/*
 * CAN.c
 *
 *  Created on: May 26, 2022
 *      Author: Kunal
 */



#include "CAN.h"


/*
 * @func 			:	CAN_Init
 * @rev				:	1
 * @Comment			:	None
 * @input param		:	mailbox
 * @output param	:	none
 * @operation		:	Configures the CAN controller as per the CAN_Config struct.
 *                      Take a look at the examples and the CAN_Config structure for
 *                      more information
 */
int CAN_Init(CAN_Init_Typedef *init)
{
    RCC->APB1ENR &= ~RCC_APB1ENR_CAN1EN;				// CAN1의 클럭 비활성화

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;	// GPIOA & AFIO클럭 활성화
    // GPIOA 핀을 CAN에서 쓰지는 않지만 AFIO는 GPIO alternative func를 설정하기 위해 필요한 모듈이므로 활성화
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;	// GPIOB 활성화

    // PC, PD핀 사용할 경우 같이 활성화 필요
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPDEN | RCC_APB2ENR_AFIOEN;

    // CAN_TX 핀을 GPIOB 포트의 PB9 핀으로 설정
    // 출력모드의 핀설정 : 출력속성과 출력 속도 설정 필요
    GPIOB->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9;		// CNF9 레지스터 설정
    GPIOB->CRH &= ~GPIO_CRH_CNF9_0;						// CNF9 레지스터의 MODE9 비트를 0으로 설정

    // CAN_RX 핀을 GPIOB 포트의 PB8 핀으로 설정
    // 입력모드의 핀설정 :
    GPIOB->CRH |= GPIO_CRH_CNF8_0;						// CNF8 레지스터 설정
    GPIOB->CRH &= ~(GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8);	// CNF8 레지스터의 MODE8 비트를 0으로, CNF[1:0]비트를 00으로 설정

    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;					// CAN1 클럭 활성화

    // CAN 제어 레지스터 (MCR)의 INRQ 비트를 1로 설정 : 컨트롤러를 초기화모드로 설정
    init->CAN_INSTANCE->MCR |= CAN_MCR_INRQ;

    // 초기화 구조체에서 전달된 CAN 인스턴스의 MCR 레지스터에 CAN_MCR_NART 비트를 1로 설정 : 비자동전송모드 비활성화
    init->CAN_INSTANCE->MCR |= CAN_MCR_NART;

    // 초기화 구조체에서 전달된 인터럽트 설정을 CAN 인스턴스의 IER 레지스터에 반영 : 해당 인터럽트 활성화
    init->CAN_INSTANCE->IER |= init->interrupt;

    // 초기화 구조체에서 전달된 baudrate 값을 CAN 인스턴스의 BTR 레지스터(CAN통신 속도와 관련, 전송속도 설정)에 설정
    init->CAN_INSTANCE->BTR = init->baudrate;

    return 1;
}

// 필터 초기화 함수
int CAN_Filter_Init(CAN_Init_Typedef *init, CAN_Filter_TypeDef *filter)
{
	uint32_t can_id = 0;

	// CAN_FMR_FINIT 비트를 설정하여 필터 모드로 진입
	init -> CAN_INSTANCE -> FMR |= CAN_FMR_FINIT;

	if(filter->filter_id > 13)
	{
		return -1;	// ID>13 이면, -1 반환해서 잘못된 필터 ID임을 나타내준다.
	}
	else
	{
// ID INFORMATION
		if(filter -> id_type == CAN_ID_Standard)	// 표준 타입일 경우 왼쪽으로 21칸 이동해서 CAN_ID설정
		{
			can_id = (filter->ID << 21) | 0;
		}
		else	// 확장 타입일 경우 CNA_ID = 3비트 이동 후 4 더해 설정
		{
			can_id = (filter->ID << 3) | 4;
		}

		if(filter -> frame_type == CAN_Frame_Remote)	// 원격이면, '2' or 연산
		{
			can_id |= 2;
		}

		// FA1R 레지스터에서 해당 필터 ID 비트를 해제하고, FS1R 레지스터에서 해당 필터 ID 비트를 설정
		// 필터링을 위한 스케일링 비트 설정
		// FA1R : 필터의 활성화 여부 결정 레지스터. 1이면 활성화 / 0이면 비활성화
		// FS1R : 필터의 스케일링 비트 설정 레지스터. 1이면 32비트 스케일링모드 / 0이면 16비트 스케일링모드
		init -> CAN_INSTANCE -> FA1R &= ~(1 << filter -> filter_id);
		init -> CAN_INSTANCE -> FS1R |=  (1 << filter -> filter_id);

		// 레지스터 배열에서 해당 필터 ID에 대한 필터 레지스터 FR1과 FR2 값을 can_id로 설정
		init -> CAN_INSTANCE -> sFilterRegister[filter->filter_id].FR1 = can_id;
		init -> CAN_INSTANCE -> sFilterRegister[filter->filter_id].FR2 = can_id;

		// FFA1R 레지스터에서 해당 필터 ID 비트를 해제하고, FA1R레지스터에서 해당 필터 ID비트를 설정
		// FFA1R : 필터의 FIFO할당을 설정하는 레지스터. 1이면 FIFO1에 할당 / 0이면 FIFO0에 할당
		init -> CAN_INSTANCE -> FFA1R &= ~(1 << filter->filter_id);
		init -> CAN_INSTANCE -> FA1R  |= (1 << filter->filter_id);

		// FMR 레지스터의 FINIT 비트를 0으로 설정하여 필터 초기화 모드를 종료
		init -> CAN_INSTANCE -> FMR &= ~CAN_FMR_FINIT;

	}
	return 1;
}

void CAN_Start(CAN_Init_Typedef *init)
{
	init -> CAN_INSTANCE -> MCR &= ~CAN_MCR_SLEEP;			// 슬립모드종료->CAN컨트롤러:동작모드
	init -> CAN_INSTANCE -> MCR &= ~CAN_MCR_INRQ;			// 초기화요청모드 종료
	while((init -> CAN_INSTANCE -> MSR & CAN_MSR_SLAK)){}	// SLAK비트 슬립상태인지 확인하며 슬립모드가 종료할때까지 대기
	while((init -> CAN_INSTANCE ->MSR & CAN_MSR_INAK));		// INAK비트 초기화상태인지 확인하며 정상동작모드로 전환될때까지 대기
}

void CAN_Send_Packet(CAN_Init_Typedef *init, CAN_TX_Typedef *tx)
{
	// 이전에 전송된 데이터들 초기화
	init -> CAN_INSTANCE -> sTxMailBox[0].TDHR &= ~0xFFFFFFFF;
	init -> CAN_INSTANCE -> sTxMailBox[0].TDLR &= ~0xFFFFFFFF;
	init -> CAN_INSTANCE -> sTxMailBox[0].TDTR &= ~0xFFFFFFFF;
	init -> CAN_INSTANCE -> sTxMailBox[0].TIR  &= ~0xFFFFFFFF;
//---------------------------------------------------------------------------------------------------------------------
	// 표준ID = 11비트 , 확장ID = 29비트 로 배치가 달라서 TIR의 적절한 위치에 배치하기 위해 조정
	// TIR 레지스터의 2번쨰 비트 : CAN 프레임 타입을 나타내는 RTR 비트
	// 표준id와 확장id는 RTR비트 값이 다르므로 해당 비트를 적절히 설정해야한다.
	switch (tx->id_type)
	{
		case CAN_ID_Standard:
		{
			init -> CAN_INSTANCE -> sTxMailBox[0].TIR  = tx->ID << 21;
			init -> CAN_INSTANCE -> sTxMailBox[0].TIR  &= ~1 << 2;
		}
			break;
		case CAN_ID_Extended:
		{
			init -> CAN_INSTANCE -> sTxMailBox[0].TIR  = tx->ID << 3;
			init -> CAN_INSTANCE -> sTxMailBox[0].TIR  |= 1 << 2;
		}
			break;
	}
//---------------------------------------------------------------------------------------------------------------------
	switch (tx->frame_type)
	{
		// 데이터 프레임 : 수신측에 실제 데이터 전송
		// init->CAN_INSTANCE->sTxMailBox[0].TIR 레지스터의 1번째 비트를 0으로 설정
		case CAN_Frame_Data:
		{
			init -> CAN_INSTANCE -> sTxMailBox[0].TIR  &= ~(1 << 1);
		}
			break;
		// 리모트 프레임 : 수신측에 특정 데이터나 동작을 요청
		// init->CAN_INSTANCE->sTxMailBox[0].TIR 레지스터의 1번째 비트를 1로 설정
		case CAN_Frame_Remote:
		{
			init -> CAN_INSTANCE -> sTxMailBox[0].TIR  |= (1 << 1);
		}
			break;
	}
//---------------------------------------------------------------------------------------------------------------------
	// 주어진 데이터를 사용해서 CAN패킷 구성 후, 전송

	// TDTR레지스터 : 전송할 데이터의 길이 설정
	init -> CAN_INSTANCE -> sTxMailBox[0].TDTR = tx->data_length;

	// TDTR레지스터의 TGT 비트를 0으로 설정 : '데이터의 길이가 고정되었음'을 의미
	init -> CAN_INSTANCE -> sTxMailBox[0].TDTR &= ~CAN_TDT0R_TGT;

	// TDHR레지스터의 상위 4바이트, TDLR레지스터의 하위 4바이트를 설정
	init -> CAN_INSTANCE -> sTxMailBox[0].TDHR = tx->data[7] << 24 | tx->data[6] << 16 | tx->data[5] << 8 | tx->data[4] << 0;
	init -> CAN_INSTANCE -> sTxMailBox[0].TDLR = tx->data[3] << 24 | tx->data[2] << 16 | tx->data[1] << 8 | tx->data[0] << 0;

	// TIR레지스터의 0번째 비트를 1로 설정해서 전송 시작 요청
	init -> CAN_INSTANCE -> sTxMailBox[0].TIR  |= (1 << 0);
	// 패킷이 전송되기를 기다린다. TIR레지스터의 0번째 비트가 1인 동안(전송이 진행중인 동안) 계속해서 기다림
	while(init -> CAN_INSTANCE -> sTxMailBox[0].TIR & (1 << 0)){}

}

// 주어진 CAN인스턴스에서 수신된 패킷을 읽어와 CAN_RX_Typedef 구조체에 저장
void CAN_Get_Packet(CAN_Init_Typedef *init, CAN_RX_Typedef *rx)
{
//	int fifo1_full, fifo2_full;
//	fifo1_full = (init -> CAN_INSTANCE -> RF0R & CAN_RF0R_FMP0_Msk) >> CAN_RF0R_FMP0_Pos;
//	fifo2_full = (init -> CAN_INSTANCE -> RF1R & CAN_RF1R_FMP1_Msk) >> CAN_RF1R_FMP1_Pos;

	int frame_type = 0;
	int id_type = 0;

	// 수신된 패킷 정보를 읽어, id와 frame 타입에 대한 정보 획득
	id_type =  (CAN1 -> sFIFOMailBox[0].RIR & CAN_RI0R_IDE_Msk) >> CAN_RI0R_IDE_Pos ;
	frame_type = (CAN1 -> sFIFOMailBox[0].RIR & CAN_RI0R_RTR_Msk) >> CAN_RI0R_RTR_Pos ;

	if(id_type)
	{
		//Extended ID
		rx->id_type = CAN_ID_Extended;
		rx->ID = (init -> CAN_INSTANCE -> sFIFOMailBox[0].RIR & CAN_RI0R_EXID_Msk) >> CAN_RI0R_EXID_Pos;
	}
	else
	{
		//Standard ID
		rx->id_type = CAN_ID_Standard;
		rx->ID = (init -> CAN_INSTANCE -> sFIFOMailBox[0].RIR & CAN_RI0R_STID_Msk) >> CAN_RI0R_STID_Pos;
	}

	if(frame_type)
	{
		//RTR Frame, 데이터 길이만 저장하고 값을 저장하지는 않는다.
		rx->frame_type = CAN_Frame_Remote;
		rx->data_length = (init -> CAN_INSTANCE -> sFIFOMailBox[0].RDTR & CAN_RDT0R_DLC_Msk) >> CAN_RDT0R_DLC_Pos;

		// 패킷을 읽고 처리한 후 RFOR레지스터의 CAN_RF0R_RFOM0 비트를 설정하여 수신 FIFO 0의 메일박스에서 패킷을 제거
		init -> CAN_INSTANCE -> RF0R |= CAN_RF0R_RFOM0;

		// RF0R 레지스터의 CAN_RF0R_RFOM0 비트가 0이 될 때까지 대기
		// 수신 FIFO 0의 메일박스가 비워질 때까지 대기하고 다음 패킷을 수신
		while((init -> CAN_INSTANCE -> RF0R & CAN_RF0R_RFOM0)){}
	}
	else
	{
		//Data Frame
		// 데이터를 1바이트씩 읽어와서 rx구조체의 data배열에 저장
		rx->frame_type = CAN_Frame_Data;
		rx->data_length = (init -> CAN_INSTANCE -> sFIFOMailBox[0].RDTR & CAN_RDT0R_DLC_Msk) >> CAN_RDT0R_DLC_Pos;
		for(int i = 0; i < rx->data_length; i++)
		{
			if(i < 4)
			{
				rx->data[i] =  (init -> CAN_INSTANCE -> sFIFOMailBox[0].RDLR & ( 0xFF << (8*i))) >> (8*i);
			}
			else
			{
				rx->data[i] =  (init -> CAN_INSTANCE -> sFIFOMailBox[0].RDHR & ( 0xFF << (8*(i-4)))) >> (8*(i-4));
			}
		}

		int x = (init -> CAN_INSTANCE -> RF0R & CAN_RF0R_FMP0_Msk);

		for(int i = 0; i < x; i++)
		{
			init -> CAN_INSTANCE -> RF0R |= CAN_RF0R_RFOM0;
		}

//		while((init -> CAN_INSTANCE -> RF0R & CAN_RF0R_RFOM0)){}
	}


}
