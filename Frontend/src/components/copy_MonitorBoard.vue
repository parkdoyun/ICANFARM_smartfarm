<template>
  <div class="container">
    <div class="item1">
      <div class="nav1">
        <div class="ICON"></div>
        <div style="font-size: 24px;">User Name</div>
        <div><button v-bind:title="default_hub">{{ default_hub }}</button></div>
        <!-- <div class="dropdown">
          <button class="btn btn-secondary dropdown-toggle" type="button" data-bs-toggle="dropdown" aria-expanded="false">허브명</button>
          <ul class="dropdown-menu">
            <li><a class="dropdown-item" href="#">Hub No. 1</a></li>
            <li><a class="dropdown-item" href="#">Hub No. 2</a></li>
            <li><a class="dropdown-item" href="#">Hub No. 3</a></li>
          </ul>
        </div> -->
      </div>
      <div class="nav2">
        <div><router-link to="/rpi" style="text-decoration: none; color: black;">RPi PW</router-link></div>
        <router-view/>
        <div><a href="/" style="text-decoration: none; color: black;" @click="logout">LOGOUT</a></div>
      </div>
    </div>

    <div class="uptime">
      <span>UPTIME</span>
      <span style="background-color: rgb(61, 91, 101)">{{ uptime }}h</span>
    </div>

    <div class="item2">
      <div class="monitor">
        <div class="temperature">
          <div class="Set_label">Temperature</div>
          <div class="chart-container">
            <canvas id="Temp-Chart"></canvas>
          </div>
        </div>
        <div class="humidity">
          <div class="Set_label">Humidity</div>
          <div class="chart-container">
            <canvas id="Humid-Chart"></canvas>
          </div>
        </div>
        <div class="co2">
          <div class="Set_label">CO2</div>
          <div class="chart-container">
            <canvas id="CO2-Chart"></canvas>
          </div>
        </div>
      </div>

      <div class="control">
        <div class="Set_Module">
          <div class="setting">
            <div class="name">Setting</div>
            <div style="font-size: 130%; padding: 10px; display: flex; flex-direction: column; justify-content: center; align-items: center;">
              <tbody style="border-spacing: 20px;">
                <tr style="text-align: center;">
                  <th>SENSOR</th>
                  <th>TARGET</th>
                  <th>RANGE</th>
                </tr>
                <tr>
                  <th>TEMP (°C)</th>
                  <th><input type="text" :placeholder="tempTarget" v-model="tempTarget" size="3"></th>
                  <th><input type="text" :placeholder="tempRange" v-model="tempRange" size="3"></th>
                </tr>
                <tr>
                  <th>WATER (%)</th>
                  <th><input type="text" :placeholder="humidTarget" v-model="humidTarget" size="3"></th>
                  <th><input type="text" :placeholder="humidRange" v-model="humidRange" size="3"></th>
                </tr>
                <tr>
                  <th>LIGHT (H)</th>
                  <th><input type="text" :placeholder="lightTarget" v-model="lightTarget" size="3"></th>
                  <th><input type="text" :placeholder="lightRange" v-model="lightRange" size="3"></th>
                </tr>
              </tbody>
              <button type="button" style="font-size: 24px; height: 50px; width: 100px; margin-top: 20px;" @click="openModal">SET</button>
            </div>
          </div>

          <div class="module">
            <div class="name">Module</div>
            <div>
              content
            </div>
          </div>
        </div>
        <div class="dashboard">
          <div class="name">Dashboard</div>
          <div style="background-color: white">
            <thead>
                <tr>
                  <th>Timeline</th>
                  <th>LOG</th>
                  <th>Message</th>
                </tr>
              </thead>
              <tbody>
                <tr>
                  <th>Date</th>
                  <th>log</th>
                  <th>message</th>
                </tr>
              </tbody>
          </div>
        </div>
      </div>
    </div>

    <div class="modal" v-if="isModalOpen">
      <div class="modal-content">
        <span class="close" @click="closeModal">&times;</span>
        <h2>Settings</h2>
        <p>Temperature Target : {{ tempTarget }}</p>
        <p>Temperature Range : {{ tempRange }}</p>
        <p>Humid Target : {{ humidTarget }}</p>
        <p>Humid Range : {{ humidRange }}</p>
        <p>Light Target : {{ lightTarget }}</p>
        <p>Light Range : {{ lightRange }}</p>
        <div>변경 완료</div>
      </div>
    </div>

  </div>
</template>

<script>
import Chart from 'chart.js/auto';
import { api } from "@/utils/axios";

export default {
  name: 'LineChart',
  data() {
    return {
      userName: "",
      default_hub: null,
      uptime: "",
      isModalOpen: false,
      temp_table: null,
      humid_table: null,
      co2_table: null,
      tempTarget: "",
      tempRange: "",
      humidTarget: "",
      humidRange: "",
      lightTarget: "",
      lightRange: "",
    };
  },
  async mounted(){
    this.member_id = localStorage.getItem('user');
    await api.member.getDefaultHub(this.member_id)
    .then((res) => {
      this.default_hub = res.data;
    })
    .catch((err) => {
      console.log('ERROR');
    });
    // this.renderChart();
    this.getSettings();
    setInterval(this.updateTime, 1000);
  },
  methods: {
    logout(){
      localStorage.removeItem('user');
    },
    updateTime(){
      const now = new Date();
      const hours = String(now.getHours()).padStart(2, "0");
      const minutes = String(now.getMinutes()).padStart(2, "0");
      const seconds = String(now.getSeconds()).padStart(2, "0");
      this.uptime = `${hours}:${minutes}:${seconds}`;
    },
    async getSettings() {
      console.log("허브 번호는?");
      console.log(this.default_hub);
      // await api.hub.getTempTarget(this.default_hub).then((res) => {
      //   this.tempTarget = res.data.value;
      // }).catch((err) => {
      //   console.log("온도 Target 가져오기 에러 발생!");
      //   console.log(err);
      // });
      // await api.hub.getTempRange(this.default_hub).then((res) => {
      //   this.tempRange = res.data.value;
      // }).catch ((err) => {
      //   console.log("온도 Range 가져오기 에러 발생!")
      //   console.log(err);
      // });
      // await api.hub.getHumidTarget(this.default_hub).then((res) => {
      //   this.humidTarget = res.data.value;
      // }).catch((err) => {
      //   console.log("습도 Target 가져오기 에러 발생!")
      //   console.log(err);
      // });
      // await api.hub.getHumidRange(this.default_hub).then((res) => {
      //   this.humidRange = res.data.value;
      // }).catch((err) => {
      //   console.log("습도 Range 가져오기 에러 발생!");
      //   console.log(err);
      // });

      try{
        const [tempTargetRes, tempRangeRes, humidTargetRes, humidRangeRes] = await Promise.all([
          api.hub.getTempTarget(this.default_hub),
          api.hub.getTempRange(this.default_hub),
          api.hub.getHumidTarget(this.default_hub),
          api.hub.getHumidRange(this.default_hub),
        ]);
        this.tempTarget = tempTargetRes.data.value;
        this.tempRange = tempRangeRes.data.value;
        this.humidTarget = humidTargetRes.data.value;
        this.humidRange = humidRangeRes.data.value;
      } catch (err) {
        console.log('ERROR: ', err);
        throw err;
      };

    },
    async openModal() {
      // api.hub.setTempTarget({rpi_id: this.default_hub, value: this.tempTarget}).then((res) => {
      //   console.log("온도 Target 변경 완료");
      // }).catch((err) => {
      //   console.log("온도 Target 변경 실패");
      // });
      // api.hub.setTempRange({rpi_id: this.default_hub, value: this.tempRange}).then((res) => {
      //   console.log("온도 Range 변경 완료");
      // }).catch((err) => {
      //   console.log("온도 Range 변경 실패");
      // });
      // api.hub.setHumidTarget({rpi_id: this.default_hub, value: this.humidTarget}).then((res) => {
      //   console.log("습도 Target 변경 완료");
      // }).catch((err) => {
      //   console.log("습도 Target 변경 실패");
      // });
      // api.hub.setHumidRange({rpi_id: this.default_hub, value: this.humidRange}).then((res) => {
      //   console.log("습도 Range 변경 완료");
      // }).catch((err) => {
      //   console.log("습도 Range 변경 실패");
      // });
      try{
        await Promise.all([
          api.hub.setTempTarget({rpi_id: this.default_hub, value: this.tempTarget}),
          api.hub.setTempRange({rpi_id: this.default_hub, value: this.tempRange}),
          api.hub.setHumidTarget({rpi_id: this.default_hub, value: this.humidTarget}),
          api.hub.setHumidRange({rpi_id: this.default_hub, value: this.humidRange}),
        ]);
        console.log("모든 API 콜 성공")
        this.isModalOpen = true;
      } catch (err) {
        console.log("ERROR: ", err);
      };
    },
    closeModal() {
      this.isModalOpen = false;
    },
    renderChart(){
      const temp = document.getElementById('Temp-Chart').getContext('2d');
      const humid = document.getElementById('Humid-Chart').getContext('2d');
      const co2 = document.getElementById('CO2-Chart').getContext('2d');

      this.temp_table= new Chart(temp, {
        type: 'line',
        data: {
          labels: ['10', '11', '12', '13', '14', '15', '16'],
          datasets: [{
            data: [21, 35, 76, 32, 67, 53, 81],
            fill: false,
            borderColor: 'rgb(226, 81, 80',
            tension: 0.1,
          }]
        },
        options: {
          maintainAspectRatio: false,
          responsive: true,
          plugins: {
            title: {
              display: true,
            },
            legend: {
              display: false,
            },
          },
          scales: {
            y: {
              beginAtZero: true,
            }
          }
        }
      });
      this.humid_table = new Chart(humid, {
        type: 'line',
        data: {
          labels: ['10', '11', '12', '13', '14', '15', '16'],
          datasets: [{
            data: [65, 59, 80, 81, 56, 55, 40],
            fill: false,
            borderColor: 'rgb(245, 216, 0)',
            tension: 0.1,
          }]
        },
        options: {
          maintainAspectRatio: false,
          responsive: true,
          plugins: {
            title: {
              display: true,
            },
            legend: {
              display: false,
            },
          },
          scales: {
            y: {
              beginAtZero: true,
            }
          }
        }
      });
      this.co2_table = new Chart(co2, {
        type: 'bar',
        data: {
          labels: ['10', '11', '12', '13', '14', '15', '16'],
          datasets: [{
            data: [98, 62, 81, 31, 47, 28, 54],
            fill: false,
            backgroundColor: 'rgb(75, 174, 122)',
            tension: 0.1,
          }]
        },
        options: {
          maintainAspectRatio: false,
          responsive: true,
          plugins: {
            title: {
              display: true,
            },
            legend: {
              display: false,
            },
          },
          scales: {
            y: {
              beginAtZero: true,
            }
          }
        }
      });
    },
  },
}
</script>

<style scoped>
.item1{
  display: flex;
  /* justify-content: space-between; */
  background-color: rgb(169, 201, 202);
  position: absolute;
  width: 100%;
  height: 10%;
  top: 0;
  left: 0;
}
.item1 > *{
  margin: 0px 10px;
}
.item1 > * > div{
  margin: 0px 7px;
}
.nav1{
  display: flex;
  align-items: center;
  margin-right: auto;
}
.nav2{
  display: flex;
  align-items: center;
  color: white;
  margin-left: auto;
}
.ICON{
  background-image: url("../assets/ICON_ICANFARM.png");
  background-size: cover;
  width: 81px;
  height: 91px;
}
.uptime{
  background-color: rgb(45, 51, 51);
  color: white;
  font-size: 32px;
  position: absolute;
  width: 100%;
  height: 5%;
  top: 10%;
  left: 0%;
  text-align: right;
}
.item2{
  display: flex;
  background-color: rgb(45, 51, 51);
  position: absolute;
  width: 100%;
  height: 85%;
  top: 15%;
  left: 0;
}
.monitor{
  color: white;
  font-size: 36px;
  width: 60%;
}
.monitor > * > *{
  border: 1px black solid;
}
.chart-container{
  position: relative;
  top: 0px;
  height: 10%;
  width: 100%;
  background-color: white;
}

.control{
  /* background-color: rgb(90, 100, 100); */
  position: relative;
  width: 40%;
  
}
.Set_Module{
  display: flex;
  height: 50%;
}
.name{
  color: black;
  font-size: 32px;
  font-weight: bold;
  text-align: center;
  background-color: rgb(169, 201, 202);
  /* width: 400px; */
}
/* .name > tbody > tr > th{
  margin: 0px 20px;
} */
.setting{
  background-color: rgb(90, 100, 100);
  width: 50%;
}
.module{
  background-color: rgb(90, 100, 100);
  width: 50%;
}
.dashboard{
  /* height: 50%; */
}


.modal {
  display: block;
  position: fixed;
  z-index: 1;
  left: 0;
  top: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.4);
}

.modal-content {
  background-color: white;
  margin: 15% auto;
  padding: 20px;
  border: 1px solid #888;
  width: 80%;
}

.close {
  color: #aaaaaa;
  float: right;
  font-size: 28px;
  font-weight: bold;
}

.close:hover,
.close:focus {
  color: #000;
  text-decoration: none;
  cursor: pointer;
}
</style>