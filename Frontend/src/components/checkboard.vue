<template>
  <div>
    <div class="uptime">
      <span>UPTIME</span>
      <span style="background-color: rgb(61, 91, 101)">{{ uptime }}h</span>
    </div>
    <div><a href="/" style="text-decoration: none; color: black;" @click="logout">LOGOUT</a></div>

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
                  <th><input type="text" :placeholder="lightTarget" v-model.lazy="lightTarget" size="3"></th>
                  <th><input type="text" :placeholder="lightRange" v-model.lazy="lightRange" size="3"></th>
                </tr>
              </tbody>
              <button type="button" style="font-size: 24px; height: 50px; width: 100px; margin-top: 20px;" @click="openModal">SET</button>
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
import {api} from "@/utils/axios"

export default {
  data(){
    return{
      uptime: 0,
      default_hub: null,
      isModalOpen: false,
      tempTarget: "",
      tempRange: "",
      humidTarget: "",
      humidRange: "",
      lightTarget: "",
      lightRange: "",
      startTime: null,
      intervalId: null,
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
    this.getSettings();
    const startTime = localStorage.getItem('startTime');
    if(startTime){
      this.startTime = new Date(parseInt(startTime));
      this.intervalId = setInterval(this.updateUptime, 1000);
    }
    // this.startTime = new Date();
    // this.intervalId = setInterval(this.updateUptime, 1000);
  },
  beforeDestroy(){
    clearInterval(this.intervalId);
  },
  methods: {
    logout(){
      localStorage.removeItem('user');
      localStorage.removeItem('startTime');
    },
    updateUptime(){
      const now = new Date();
      const diff = now.getTime() - this.startTime.getTime();
      this.uptime = (diff/(1000*60*60)).toFixed(2);
    },
    async getSettings(){
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
      try{
        await Promise.all([
          api.hub.setTempTarget({rpi_id: this.default_hub, value: this.tempTarget}).then((res) => console.log("TT done")),
          api.hub.setTempRange({rpi_id: this.default_hub, value: this.tempRange}).then((res) => console.log("TR done")),
          api.hub.setHumidTarget({rpi_id: this.default_hub, value: this.humidTarget}).then((res) => console.log("HT done")),
          api.hub.setHumidRange({rpi_id: this.default_hub, value: this.humidRange}).then((res) => console.log("HR done")),
        ]);
        console.log(this.tempTarget);
        console.log(this.tempRange);
        console.log(this.humidTarget);
        console.log(this.humidRange);
        
        console.log("모든 API 콜 성공")
        this.isModalOpen = true;
      } catch (err) {
        console.log("ERROR: ", err);
      };
      
    },
    closeModal() {
      this.isModalOpen = false;
    },
  },
}
</script>

<style scoped>

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