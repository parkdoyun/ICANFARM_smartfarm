<template>
  <div class="container">
    <div class="item1">
      <div class="nav1">
        <div class="ICON"></div>
        <div style="font-size: 36px;">{{ userName }}</div>
        <div><button v-bind:title="default_hub">Hub No. {{ default_hub }}</button></div>

      </div>
      <div class="nav2">
        <div><router-link to="/rpi" style="text-decoration: none; color: black;">RPi PW</router-link></div>
        <router-view/>
        <div><a href="/" style="text-decoration: none; color: black;" @click="logout">LOGOUT</a></div>
      </div>
    </div>

    <div class="uptime">
      <span style="position: absolute; right: 90px;">UPTIME</span>
      <span style="background-color: rgb(61, 91, 101); margin-right: 10px;">{{ uptime }}h</span>
    </div>

    <div class="item2">
      <div class="monitor">
        <div class="temperature" style="height: 33%;">
          <div class="Set_label">Temperature</div>
          <div style="height: 100%; display: flex; justify-content: center;">
            <div class="graph-doughnut">
              <DoughnutChart ref="tempdoughnutChart" :data="TempDonutChart" :options="DonutChartOptions"/>
              <div style="color: black; font-size: 32px; position: absolute; top: 83px; left: 105px;">{{ tempVal }}°C</div>
            </div>
            <div class="graph-line">
              <LineChart ref="templineChart" :chart-data="TempLineChart" :chart-options="lineChartOptions" />
            </div>
          </div>
        </div>
        <div class="humidity" style="height: 33%;">
          <div class="Set_label">Humidity</div>
          <div style="height: 100%; display: flex; justify-content: center;">
            <div class="graph-doughnut">
              <DoughnutChart ref="humiddoughnutChart" :data="HumidDonutChart" :options="donutChartOptions"/>
              <div style="color: black; font-size: 32px; position: absolute; top: 83px; left: 110px;">{{ humidVal }}%</div>
            </div>
            <div class="graph-line">
              <LineChart ref="humidlineChart" :chart-data="HumidLineChart" :chart-options="lineChartOptions" />
            </div>
          </div>
        </div>
        <div class="co2" style="height: 33%;">
          <div class="Set_label">CO2</div>
          <div style="height: 100%; display: flex; justify-content: center;">
            <div class="graph-doughnut">
              <DoughnutChart ref="co2doughnutChart" :data="CO2DonutChart" :options="donutChartOptions"/>
              <div style="color: black; font-size: 24px; position: absolute; top: 89px; left: 105px;">{{ co2Val }}ppm</div>
            </div>
            <div class="graph-line">
              <LineChart ref="co2lineChart" :chart-data="CO2LineChart" :chart-options="lineChartOptions" />
            </div>
          </div>
        </div>
      </div>

      <div class="control">
        <div class="Set_Module">
          <div class="setting">
            <div class="name">Setting</div>
            <div style="height: 83%; font-size: 130%; display: flex; flex-direction: column; justify-content: center; align-items: center; background-color: rgb(90, 100, 100); margin: 10px 0px;">
              <tbody style="border-spacing: 20px;">
                <tr style="text-align: center;">
                  <th>SENSOR</th>
                  <th>TARGET</th>
                  <th>RANGE</th>
                </tr>
                <tr>
                  <th>TEMP (°C)</th>
                  <th><input type="text" :placeholder="tempTarget" v-model.lazy="tempTarget" size="3"></th>
                  <th><input type="text" :placeholder="tempRange" v-model.lazy="tempRange" size="3"></th>
                </tr>
                <tr>
                  <th>WATER (%)</th>
                  <th><input type="text" :placeholder="humidTarget" v-model.lazy="humidTarget" size="3"></th>
                  <th><input type="text" :placeholder="humidRange" v-model.lazy="humidRange" size="3"></th>
                </tr>
                <tr>
                  <th>LIGHT (H)</th>
                  <th><input type="text" :placeholder="startTimeHour" v-model.lazy="startTimeHour" size="3"></th>
                  <th><input type="text" :placeholder="endTimeHour" v-model.lazy="endTimeHour" size="3"></th>
                </tr>
              </tbody>
              <button type="button" style="font-size: 24px; height: 50px; width: 100px; margin-top: 15px;" @click="openModal">SET</button>
            </div>
          </div>

          <div class="module">
            <div class="name">Module</div>
            <div style="height: 83%; display: flex; flex-direction: column; justify-content: space-between; margin: 10px 0px;">
              <div style="display: flex; justify-content: space-between">
                <div :class="{'m_humid_on': humidModule, 'm_humid_off': !humidModule}"></div>
                <div :class="{'m_light_on': lightModule, 'm_light_off': !lightModule}"></div>
              </div>
              <div style="display: flex; justify-content: space-between">
                <div :class="{'m_co2_on': co2Module, 'm_co2_off': !co2Module}"></div>
                <div :class="{'m_fan_on': fanModule, 'm_fan_off': !fanModule}"></div>
              </div>
            </div>
          </div>
        </div>
        <div class="dashboard">
          <div class="name">Notification</div>
          <div style="background-color: white; height: 86%;">
            <table style="width: 100%;">
              <thead>
                <tr style="font-size: 30px; text-align: center;">
                  <th style="width: 30%;">Timeline</th>
                  <th style="width: 20%;">LOG</th>
                  <th style="width: 50%;">Message</th>
                </tr>
              </thead>
              <tbody>
                <tr style="font-size: 24px; text-align: center;" v-for="(message, index) in messages.slice().reverse()" :key="index">
                  <td style="width: 30%;">{{ getMessageTime(message.date) }}</td>
                  <td style="width: 20%; color: red;">{{ message.log }}</td>
                  <td style="width: 50%;">{{ message.text }}</td>
                </tr>
              </tbody>
            </table>
          </div>
        </div>
      </div>
    </div>

    <div class="modal" tabindex="-1" v-if="isModalOpen">
      <div class="modal-dialog">
        <div class="modal-content">
          <div class="modal-header">
            <h5 class="modal-title"><h2>Settings</h2></h5>
            <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close" @click="closeModal"></button>
          </div>
          <div class="modal-body">
            <p>Temperature Target : {{ tempTarget }}</p>
            <p>Temperature Range : {{ tempRange }}</p>
            <p>Humid Target : {{ humidTarget }}</p>
            <p>Humid Range : {{ humidRange }}</p>
            <p>Start Time : {{ startTimeHour }}</p>
            <p>End Time : {{ endTimeHour }}</p>
            <div>변경 완료</div>
          </div>
        </div>
      </div>
    </div>

  </div>
</template>

<script>
import { api } from "@/utils/axios";
import DoughnutChart from '@/components/DoughnutChart.vue';
import LineChart from '@/components/LineChart.vue';

export default {
  components: {
    DoughnutChart,
    LineChart,
  },
  data() {
    return {
      userName: "",
      default_hub: null,
      uptime: 0,
      intervalId: null,
      isModalOpen: false,
      messages: [],
      temp_table: null,
      humid_table: null,
      co2_table: null,
      tempVal: 0,
      humidVal: 0,
      co2Val: 0,
      tempTarget: "",
      tempRange: "",
      humidTarget: "",
      humidRange: "",
      lightTarget: "",
      lightRange: "",
      startTimeHour: null,
      endTimeHour: null,
      humidModule: false,
      lightModule: false,
      co2Module: false,
      fanModule: false,
      TempDonutChart: {
        labels: ['Red', 'Gray'],
        datasets: [
          {
            data: [25, 25],
            backgroundColor: ['#FF6384', '#D9D9D9'],
            borderWidth: 1,
          },
        ],
      },
      TempLineChart: {
        labels: [''],
        datasets: [
          {
            borderColor: 'rgb(255, 99, 132)',
            data: [0],
          },
        ],
      },
      HumidDonutChart: {
        labels: ['Yellow', 'Gray'],
        datasets: [
          {
            data: [25, 25],
            backgroundColor: ['#F5D800', '#D9D9D9'],
            borderWidth: 1,
          },
        ],
      },
      HumidLineChart: {
        labels: [''],
        datasets: [
          {
            label: 'My First dataset',
            borderColor: 'rgb(255, 99, 132)',
            data: [0],
          },
        ],
      },
      CO2DonutChart: {
        labels: ['Green', 'Gray'],
        datasets: [
          {
            data: [25, 25],
            backgroundColor: ['#4BAE7A', '#D9D9D9'],
            borderWidth: 1,
          },
        ],
      },
      CO2LineChart: {
        labels: [''],
        datasets: [
          {
            label: 'My First dataset',
            borderColor: 'rgb(255, 99, 132)',
            data: [0],
          },
        ],
      },

      donutChartOptions: {
        responsive: false,
        cutout: 90,
        plugins: {
          legend: {
            display: false,
          },
        },
      },
      lineChartOptions: {
        plugins: {
          legend: {
            display: false,
          },
        },
      },
    };
  },
  async mounted(){
    this.member_id = localStorage.getItem('user');
    this.userName = localStorage.getItem('username');
    await api.member.getDefaultHub(this.member_id)
    .then((res) => {
      this.default_hub = res.data;
    }).catch((err) => {
      console.log(err);
    });
    await api.hub.getModuleInfo(this.default_hub)
    .then((res) => {
      console.log(this.default_hub);
      console.log(res);
      this.humidModule = res.data.isHumid;
      this.lightModule = res.data.isLight;
      this.co2Module = res.data.isCo2;
      this.fanModule = res.data.isFan;
      console.log(humidModule);
      console.log(lightModule);
      console.log(co2Module);
      console.log(fanModule);
    }).catch((err) => {
    })

    this.getSettings();
    const startTime = localStorage.getItem('startTime');
    if(startTime){
      this.startTime = new Date(parseInt(startTime));
      this.intervalId = setInterval(this.updateUptime, 1000);
    }

    this.socket = new WebSocket("ws://k8a206.p.ssafy.io:8090/api/socket");
    this.socket.onopen = () => {
      console.log("WEB SOCKET CONNECTED");
    };
    this.socket.onmessage = ({ data }) => {
      console.log(data);
      this.addMessage(data);
    }

    window.addEventListener('resize', this.handleResize);
    this.fetchData();
    setInterval(this.fetchData, 15*1000);
  },
  beforeRouteLeave(to, from, next) {
  localStorage.setItem('startTime', this.startTime.getTime());
  next();
  },
  methods: {
    logout(){
      localStorage.removeItem('user');
      localStorage.removeItem('startTime');
      localStorage.removeItem('username');
    },
    addMessage(data){
      const message = {
        date: new Date(),
        log: "Warning",
        text: data,
      };
      this.messages.push(message);
    },
    getMessageTime(data){
      const options = {hour: "numeric", minute: "numeric"};
      return data.toLocaleString(undefined, options);
    },
    fetchData() {
      api.hub.getTemp(this.default_hub)
        .then((res) => {
          // const newItem = res.data.slice(-1)[0];
          const newItem = res.data[0];
          if(this.tempVal != parseInt(newItem.value)){
            this.tempVal = parseInt(newItem.value);
            console.log(newItem.value);
            this.$set(this.TempDonutChart.datasets[0].data, 0, newItem.value);
            this.$set(this.TempDonutChart.datasets[0].data, 1, 50 - newItem.value);
            this.$refs.tempdoughnutChart.renderChart();
          }
          const date = new Date(newItem.date);
          const hours = date.getHours();
          const minutes = date.getMinutes();
          const label = `${hours}:${minutes}`;

          this.TempLineChart.labels.push(label);
          this.TempLineChart.datasets[0].data.push(newItem.value);

          if(this.TempLineChart.labels.length>10){
            this.TempLineChart.labels.shift();
            this.TempLineChart.datasets[0].data.shift();
          }
          this.$refs.templineChart.renderChart();

        })
        .catch((err) => {
          console.log(err);
        });
      api.hub.getHumid(this.default_hub)
        .then((res) => {
          // const newItem = res.data.slice(-1)[0];
          const newItem = res.data[0];
          if(this.humidVal != parseInt(newItem.value)){
            this.humidVal = parseInt(newItem.value);
            console.log(newItem.value);
            this.$set(this.HumidDonutChart.datasets[0].data, 0, newItem.value);
            this.$set(this.HumidDonutChart.datasets[0].data, 1, 50 - newItem.value);
            this.$refs.humiddoughnutChart.renderChart();
          }
          const date = new Date(newItem.date);
          const hours = date.getHours();
          const minutes = date.getMinutes();
          const label = `${hours}:${minutes}`;

          this.HumidLineChart.labels.push(label);
          this.HumidLineChart.datasets[0].data.push(newItem.value);

          if(this.HumidLineChart.labels.length>10){
            this.HumidLineChart.labels.shift();
            this.HumidLineChart.datasets[0].data.shift();
          }
          this.$refs.humidlineChart.renderChart();
        })
        .catch((err) => {
          console.log(err);
        });
      api.hub.getCO2(this.default_hub)
        .then((res) => {
          // const newItem = res.data.slice(-1)[0];
          const newItem = res.data[0];
          if(this.co2Val != parseInt(newItem.value)){
            this.co2Val = parseInt(newItem.value);
            console.log(newItem.value);
            this.$set(this.CO2DonutChart.datasets[0].data, 0, newItem.value);
            this.$set(this.CO2DonutChart.datasets[0].data, 1, 50 - newItem.value);
            this.$refs.co2doughnutChart.renderChart();
          }
          const date = new Date(newItem.date);
          const hours = date.getHours();
          const minutes = date.getMinutes();
          const label = `${hours}:${minutes}`;

          this.CO2LineChart.labels.push(label);
          this.CO2LineChart.datasets[0].data.push(newItem.value);

          if(this.CO2LineChart.labels.length>10){
            this.CO2LineChart.labels.shift();
            this.CO2LineChart.datasets[0].data.shift();
          }
          this.$refs.co2lineChart.renderChart();
        })
        .catch((err) => {
          console.log(err);
        });
    },
    updateUptime(){
      const now = new Date();
      const diff = now.getTime() - this.startTime.getTime();
      this.uptime = (diff/(1000*60*60)).toFixed(2);
    },
    async getSettings() {
      try{
        const [tempTargetRes, tempRangeRes, humidTargetRes, humidRangeRes, lightRes] = await Promise.all([
          api.hub.getTempTarget(this.default_hub),
          api.hub.getTempRange(this.default_hub),
          api.hub.getHumidTarget(this.default_hub),
          api.hub.getHumidRange(this.default_hub),
          api.hub.getLightSet(this.default_hub),
        ]);
        this.tempTarget = tempTargetRes.data.value;
        this.tempRange = tempRangeRes.data.value;
        this.humidTarget = humidTargetRes.data.value;
        this.humidRange = humidRangeRes.data.value;
        this.startTimeHour = Number.parseInt(lightRes.data.startTime.slice(11, 13));
        this.endTimeHour = Number.parseInt(lightRes.data.endTime.slice(11, 13));
      } catch (err) {
        console.log('ERROR: ', err);
        throw err;
      };

    },
    openModal() {
      const now = new Date();
      const year = now.getFullYear();
      const month = String(now.getMonth() + 1).padStart(2, "0");
      const day = String(now.getDate()).padStart(2, "0");

      const formatTime = (time) => String(time).padStart(2, "0");
      api.hub.getAllSetting({
        rpi_id: this.default_hub,
        tempTarget: this.tempTarget,
        tempRange: this.tempRange,
        humidTarget: this.humidTarget,
        humidRange: this.humidRange,
        startTime: `${year}-${month}-${day}T${formatTime(this.startTimeHour)}:00:00`,
        endTime: `${year}-${month}-${day}T${formatTime(this.endTimeHour)}:00:00`,
      }).then((res) => {
        console.log("모든 API 콜 성공");
        this.isModalOpen = true;
      }).catch((err) => {
        console.log(err);
      });
    },
    closeModal() {
      this.isModalOpen = false;
    },

  },
}
</script>

<style scoped>
/* div{
  border: 1px black solid;
} */
.item1{
  display: flex;
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
  background-image: url("@/assets/ICON_ICANFARM.png");
  background-size: cover;
  width: 81px;
  height: 91px;
}
.uptime{
  background-color: rgb(45, 51, 51);
  color: white;
  font-size: 28px;
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
  height: 100%;
}
.Set_label{
  height: 20%;
  font-size: 30px;
}

.graph-doughnut{
  height: 80%;
  width: 25%;
  background-color: white;
  position: relative;
}
.graph-doughnut > *{
  position: absolute;
  top: 0;
  bottom: 0;
  left: 30px;
}
.graph-line{
  height: 80%;
  width: 75%;
  background-color: white;
  position: relative;
}

.control{
  /* background-color: rgb(90, 100, 100); */
  position: relative;
  width: 40%;
  display: flex;
  flex-direction: column;
  height: 100%;
}
.Set_Module{
  display: flex;
  flex: 1;
}
.name{
  color: black;
  font-size: 32px;
  font-weight: bold;
  text-align: center;
  background-color: rgb(169, 201, 202);
  height: 12%;
}

.setting{
  width: 54%;
  height: 100%;
  margin: 0% 1%;
}
.module{
  background-color: #2D3333;
  width: 46%;
  height: 100%;
  margin: 0% 1%;
}

.m_humid_on{
  background-image: url("@/assets/m_water_on.png");
  background-size: cover;
  background-color: #5A6464;
  width: 160px;
  height: 160px;
}
.m_humid_off{
  background-image: url("@/assets/m_water_off.png");
  background-size: cover;
  background-color: #000000;
  width: 160px;
  height: 160px;
}
.m_light_on{
  background-image: url("@/assets/m_light_on.png");
  background-size: cover;
  background-color: #5A6464;
  width: 160px;
  height: 160px;
}
.m_light_off{
  background-image: url("@/assets/m_light_off.png");
  background-size: cover;
  background-color: #000000;
  width: 160px;
  height: 160px;
}
.m_co2_on{
  background-image: url("@/assets/m_co2_on.png");
  background-size: cover;
  background-color: #5A6464;
  width: 160px;
  height: 160px;
}
.m_co2_off{
  background-image: url("@/assets/m_co2_off.png");
  background-size: cover;
  background-color: #000000;
  width: 160px;
  height: 160px;
}
.m_fan_on{
  background-image: url("@/assets/m_wind_on.png");
  background-size: cover;
  background-color: #5A6464;
  width: 160px;
  height: 160px;
}
.m_fan_off{
  background-image: url("@/assets/m_wind_off.png");
  background-size: cover;
  background-color: #000000;
  width: 160px;
  height: 160px;
}


.dashboard{
  flex: 1;
  margin: 0% 1%;
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