<template>
  <div class="container">
    <div class="Nav">
      <div>
        <div class="item1" style="background-color: rgb(169, 201, 202);">
          <div class="ICON" style="margin: 10px;"></div>
          <div class="LOGO" style="margin: 5px;"></div>
        </div>
        <div style="margin: 20% 0% 0% 0%;">
          <div style="display: flex; align-items: center;">
            <div class="MemIcon" style="margin: 10px;"></div>
            <router-link to="/admin/member" style="position: relative; width: 80%; text-decoration: none; color: white; font-size: 36px;">회원 등록  &gt;&gt;</router-link>
          </div>
          <div>
            <div style="display: flex; align-items: center; background-color: rgb(169, 201, 202);">
              <div class="HubIcon" style="margin: 10px;"></div>
              <router-link to="/admin/hub" style="position: relative; width: 80%; text-decoration: none; color: white; font-size: 36px;">허브 등록  &gt;&gt;</router-link>
            </div>
          </div>
          <div>
            <div style="display: flex; align-items: center;">
              <div class="MamIcon" style="margin: 10px;"></div>
              <router-link to="/admin/manage" style="position: relative; width: 80%; text-decoration: none; color: white; font-size: 36px;">회원 관리  &gt;&gt;</router-link>
            </div>
          </div>
        </div>
      </div>
      <div><router-link to="/" style="text-decoration: none; color: white; font-size: 48px;">&lt;&lt; LOGIN</router-link></div>
    </div>
    <router-view/>

    <div class="item2">
      <tbody style="width: 80%;">
        <th style="width: 15%; text-align: right;">회원:</th>
        <th style="width: 50%;"><input type="text" placeholder="E-mail을 입력하세요." style="width: 100%; box-sizing: border-box;" v-model="userEmail" @keyup.enter="emailCheck"></th>
        <th style="width: 15%;"><button @click="emailCheck">검색</button></th>
      </tbody>

      <div v-if="showTable" style="width: 80%">
        <div style="font-size: 32px; text-align: center">사용할 모듈을 선택하세요.</div>
        <p></p>
        <div style="display: flex; justify-content: center;">
          <table class="table table-striped table-bordered" style="width: 70%;">
            <thead>
              <tr style="font-size: 32px; text-align: center;">
                <th>User ID</th>
                <th>WATER</th>
                <th>LIGHT</th>
                <th>CO2</th>
                <th>WIND</th>
                <th></th>
              </tr>
            </thead>
            <tbody>
              <tr style="font-size: 28px; text-align: center;">
                <td>{{ userID }}</td>
                <td>
                  <div class="form-check form-switch">
                    <input class="form-check-input" type="checkbox" role="switch" id="flexSwitchCheckDefault" v-model="waterValue" @click="water_toggle">
                  </div>
                </td>
                <td>
                  <div class="form-check form-switch">
                    <input class="form-check-input" type="checkbox" role="switch" id="flexSwitchCheckDefault" v-model="lightValue" @click="light_toggle">
                  </div>
                </td>
                <td>
                  <div class="form-check form-switch">
                    <input class="form-check-input" type="checkbox" role="switch" id="flexSwitchCheckDefault" v-model="co2Value" @click="co2_toggle">
                  </div>
                </td>
                <td>
                  <div class="form-check form-switch">
                    <input class="form-check-input" type="checkbox" role="switch" id="flexSwitchCheckDefault" v-model="windValue" @click="wind_toggle">
                  </div>
                </td>
                <td>
                  <div style="display: flex; justify-content: center; align-items: center;">
                    <button type="button" class="btn btn-secondary" @click="saveModule">SAVE</button>
                  </div>
                </td>
              </tr>
            </tbody>
          </table>

        </div>
      </div>

    </div>

  </div>
</template>

<script>
import { api } from "@/utils/axios"

export default {
  data() {
    return{
      // userSerial: "",
      // isSerialAvailable: false,
      userEmail: "",
      userID: "",
      showTable: false,
      isModalOpen: false,
      waterValue: false,
      lightValue: false,
      co2Value: false,
      windValue: false,
    }
  },
  methods: {
    emailCheck(){
      api.member.getUserID(this.userEmail).then((res) => {
        this.userID = res.data;
        this.showTable = true;
        alert("회원 조회가 완료되었습니다.");
      }).catch((err) => {
        alert("등록되지 않은 이메일입니다.");
        console.log(err);
      });
    },
    water_toggle() {
      this.waterValue = !this.waterValue;
      console.log("water");
      console.log(this.waterValue);
    },
    light_toggle(){
      this.lightValue = !this.lightValue;
      console.log("light");
      console.log(this.lightValue);
    },
    co2_toggle(){
      this.co2Value = !this.co2Value;
      console.log("co2");
      console.log(this.co2Value);
    },
    wind_toggle(){
      this.windValue = !this.windValue;
      console.log("wind");
      console.log(this.windValue);
    },
    saveModule(){
      api.admin.setMemberRPi({
        memberId: this.userID,
        co2Module: this.co2Value,
        lightModule: this.lightValue,
        humidModule: this.waterValue,
        fanModule: this.windValue,
      }).then((res) => {
        alert("허브의 모듈 저장이 완료되었습니다.");
      }).catch((err) => {
        console.log(err);
        alert("사용 가능한 허브가 존재하지 않습니다.");
      });
    },
  },
}
</script>

<style scoped>
.container{
  display: flex;
}
.Nav{
  background-color: rgb(61, 91, 101);
  position: absolute;
  width: 20%;
  height: 100%;
  top: 0;
  left: 0;
  display: flex;
  flex-direction: column;
  justify-content: space-between;
}
.item1{
  display: flex;
  align-items: center;
}
.ICON{
  background-image: url("../assets/ICON_ICANFARM.png");
  background-size: cover;
  width: 90px;
  height: 100px;
}
.LOGO{
  background-image: url("../assets/LINE_ICANFARM.png");
  background-size: cover;
  width: 235px;
  height: 39px;
}
.MemIcon{
  background-image: url("../assets/ICON_Members.png");
  background-size: cover;
  position: relative; 
  width: 20%;
  height: 70px;
  /* width: 70px;
  height: 70px; */
}
.HubIcon{
  background-image: url("../assets/ICON_Hub.png");
  background-size: cover;
  position: relative; 
  width: 20%;
  height: 70px;
}
.MamIcon{
  background-image: url("../assets/ICON_Member.png");
  background-size: cover;
  position: relative; 
  width: 20%;
  height: 70px;
}

.item2{
  position: absolute;
  width: 80%;
  height: 100%;
  top: 0;
  left: 20%;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
}
.item2 tbody{
  border-spacing: 30px 70px;
  font-size: 36px;
}
.item2 button{
  display: block;
  margin: 0 auto;
  width: 200px;
}
::placeholder {
  text-align: center;
}

</style>