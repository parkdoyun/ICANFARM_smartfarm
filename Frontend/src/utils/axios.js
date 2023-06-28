import axios from "axios";

const request = axios.create({
    baseURL: "http://k8a206.p.ssafy.io:8090",
  })

export const api = {
    member: {
        // 회원 로그인
        // check -> LoginBoard
        login: ({email, passwd}) => {
            return request.post('/api/login', {email, passwd});
        },
        // RPi 비밀번호 조회
        // check -> AccountBoard, RPiBoard
        getRPiPW: (member_id) => {
            return request.get(`/api/rpi/pw/${member_id}`);
        },
        // RPi 비밀번호 변경
        // check -> RPiBoard
        setRPiPW: ({member_id, pwd}) => {
            return request.post(`/api/rpi/pw/${member_id}`, {pwd});
        },
        // 허브 리스트
        getHubs: (member_id) => {
            return request.get(`/api/hub/${member_id}`);
        },
        // 디폴트 허브 조회
        getDefaultHub: (member_id) => {
            return request.get(`/api/hub/default/${member_id}`);
        },
        getUserID: (email) => {
            return request.get(`/api/memberId/${email}`);
        },
    },
    hub: {
        // 온도 target 설정 조회
        getTempTarget: (rpi_id) => {
            return request.get(`/api/setting/target/temp/${rpi_id}`);
        },
        // 온도 range 설정 조회
        getTempRange: (rpi_id) => {
            return request.get(`/api/setting/range/temp/${rpi_id}`);
        },
        // 온도 target 설정 변경
        setTempTarget: ({rpi_id, value}) => {
            return request.post(`/api/setting/target/temp/${rpi_id}`, {value});
        },
        // 온도 range 설정 변경
        setTempRange: ({rpi_id, value}) => {
            return request.post(`/api/setting/range/temp/${rpi_id}`, {value});
        },
        // 습도 target 설정 조회
        getHumidTarget: (rpi_id) => {
            return request.get(`/api/setting/target/humid/${rpi_id}`);
        },
        // 습도 range 설정 조회
        getHumidRange: (rpi_id) => {
            return request.get(`/api/setting/range/humid/${rpi_id}`);
        },
        // 습도 target 설정 변경
        setHumidTarget: ({rpi_id, value}) => {
            return request.post(`/api/setting/target/humid/${rpi_id}`, {value});
        },
        // 습도 range 설정 변경
        setHumidRange: ({rpi_id, value}) => {
            return request.post(`/api/setting/range/humid/${rpi_id}`, {value});
        },
        // 조명 설정 정보 조회
        getLightSet: (rpi_id) => {
            return request.get(`/api/setting/light/${rpi_id}`);
        },
        // 조명 설정 변경
        setLightSet: ({rpi_id, startTime, endTime}) => {
            return request.post(`/api/setting/light/${rpi_id}`, {startTime, endTime});
        },
        getModuleInfo: (rpi_id) => {
            return request.get(`/api/moduleInfo/${rpi_id}`);
        },

        // 온도 정보 조회
        getTemp: (rpi_id) => {
            return request.get(`/api/temp/${rpi_id}`);
        },
        // 습도 정보 조회
        getHumid: (rpi_id) => {
            return request.get(`/api/humid/${rpi_id}`);
        },
        // CO2 정보 조회
        getCO2: (rpi_id) => {
            return request.get(`/api/co2/${rpi_id}`);
        },
        // 한 번에 설정 변경
        getAllSetting: ({rpi_id, tempTarget, tempRange, humidTarget, humidRange, startTime, endTime}) => {
            return request.post(`/api/setting/all/${rpi_id}`, {tempTarget, tempRange, humidTarget, humidRange, startTime, endTime});
        }

    },
    admin: {
        // 이메일 중복 확인
        checkEmail: (email) => {
            return request.get(`/admin/validation/email/${email}`);
        },
        // 회원 정보 저장
        setMember: ({email, passwd, name}) => {
            return request.post('/admin/member', {email, passwd, name});
        },
        // 시리얼 번호 중복 검사
        checkSerial: (serial) => {
            return request.get(`/admin/validation/serial/${serial}`);
        },
        // 라즈베리파이 기기 정보 저장
        setRPiInfo: (serial) => {
            return request.post('/admin/rpi', {serial});
        },
        // 회원 정보 조회
        checkMember: (email) => {
            return request.get(`/admin/member/${email}`);
        },
        // RPi 등록
        setMemberRPi: ({memberId, co2Module, lightModule, humidModule, fanModule}) => {
            return request.post('/admin/member/rpi', {memberId, co2Module, lightModule, humidModule, fanModule});
        },
        // RPi 제거
        delMemberRPi: ({member_id, rpi_id}) => {
            return request.delete(`/admin/member/rpi/${member_id}/${rpi_id}`);
        }
    }
}

export default request