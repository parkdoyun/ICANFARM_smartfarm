.<template>
  <div class="container">
    <div class="Nav">
      <div class="item1">
        <div class="ICON"></div>
        <div class="LOGO"></div>
      </div>

      <div><router-link to="/" style="text-decoration: none; color: white; font-size: 48px;">&lt;&lt; LOGIN</router-link></div>
    </div>
    <router-view/>

    <div class="item2">
      <tbody>
        <tr>
          <th>이메일:</th>
          <th><input type="text" v-model="email"></th>
        </tr>
        <tr>
          <th>이름:</th>
          <th><input type="text" v-model="name"></th>
        </tr>
        <tr>
          <th></th>
          <th><button @click="getInfo()">조회</button></th>
        </tr>
        <tr>
          <th><p></p></th>
        </tr>
        <tr>
          <th>ID:</th>
          <th><div style="border: 1px black solid;">{{ id }}</div></th>
        </tr>
        <tr>
          <th>PW:</th>
          <th><div style="border: 1px black solid;">{{ pw }}</div></th>
        </tr>
        <tr>
          <th>RPi PW:</th>
          <th><div style="border: 1px black solid;">{{ rpi_pw }}</div></th>
        </tr>
      </tbody>
    </div>
  </div>
</template>

<script>

import { api } from "@/utils/axios"

export default {
  data() {
    return {
      email: "",
      name: "",
      id: "",
      pw: "",
      rpi_pw: "",
    };
  },
  methods: {
    getInfo() {
      console.log("find click")
      const member = {
        email: this.email,
        // name: this.name,
      };
      api.member.getRPiPW(member.email).then((response) => {
        this.rpi_pw = response.data;
      });
      console.log("end click")
    },
  }

}
</script>

<style scoped>
.container{
  display: flex;
}
.Nav{
  background-color: rgb(169, 201, 202);
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
  /* justify-content: center; */
  align-items: center;
}
.ICON{
  background-image: url("../assets/ICON_ICANFARM.png");
  background-size: cover;
  width: 90px;
  height: 100px;
  /* top: 1%;
  Left: 1%; */
}
.LOGO{
  /* border: solid 1px black; */
  background-image: url("../assets/LINE_ICANFARM.png");
  background-size: cover;
  width: 235px;
  height: 39px;
  /* position: relative;
  left: 6%;
  top: 4%; */
  /* margin: auto; */
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
  border-spacing: 20px 20px;
  font-size: 36px;
}
.item2 button{
  display: block;
  margin: 0 auto;
  width: 150px;
}

</style>