<template>
  <div class="container">
    <div class="item1">
      <div class="nav1">
        <div class="ICON"></div>
        <div style="font-size: 24px;">User Name</div>
        <div><button v-bind:title="default_hub">{{ default_hub }}</button></div>
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
    this.getSettings();
  },
  methods: {
    logout(){
      localStorage.removeItem('user');
    },
    async getSettings() {
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
    openModal(){
      api.hub.setTempTarget({rpi_id: this.default_hub, value: this.tempTarget}).then((res) => {
        console.log(res.data);
      }).catch((err) => {
        console.log(err);
      })
    },

    // async openModal() {
    //   try{
    //     await Promise.all([
    //       api.hub.setTempTarget({rpi_id: this.default_hub, value: this.tempTarget}),
    //       api.hub.setTempRange({rpi_id: this.default_hub, value: this.tempRange}),
    //       api.hub.setHumidTarget({rpi_id: this.default_hub, value: this.humidTarget}),
    //       api.hub.setHumidRange({rpi_id: this.default_hub, value: this.humidRange}),
    //     ]);
    //     console.log("모든 API 콜 성공")
    //     this.isModalOpen = true;
    //   } catch (err) {
    //     console.log("ERROR: ", err);
    //   };
    // },
    closeModal() {
      this.isModalOpen = false;
    },

  },
}
</script>