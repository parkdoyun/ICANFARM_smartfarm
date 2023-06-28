<template>
  <div class="container">
    
    <div class="item">
      <div class="chart-wrapper">
      </div>
      <div class="graph-line">
        <LineChart ref="templineChart" :chart-data="TempLineChart" :chart-options="lineChartOptions" />
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
      default_hub: null,
      tempVal: 0,
      TempDonutChart: {
        labels: ['Red', 'Gray'],
        datasets: [
          {
            data: [0, 0],
            backgroundColor: ['#FF6384', '#D9D9D9'],
            borderWidth: 1,
          },
        ],
      },
      TempLineChart: {
        labels: ['', '', '', '', '', '', '', '', '', ''],
        datasets: [
          {
            borderColor: 'rgb(255, 99, 132)',
            data: [0, 10, 5, 2, 20, 30, 45],
          },
        ],
      },
      donutChartOptions: {
        responsive: true,
        maintainAspectRatio: false,
        cutoutPercentage: 50,
        legend: {
          display: false,
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
  async mounted() {
    this.member_id = localStorage.getItem('user');
    await api.member.getDefaultHub(this.member_id)
      .then((res) => {
        this.default_hub = res.data;
      })
      .catch((err) => {
        console.log(err);
      });

      
    this.fetchData();
    setInterval(this.fetchData, 2000);
  },
  methods: {
    fetchData() {
      api.hub.getCO2(this.default_hub)
        .then((res) => {
          const newItem = res.data.slice(-1)[0];
          const date = new Date(newItem.date);
          const hours = date.getHours();
          const minutes = date.getMinutes();
          const label = `${hours}:${minutes}`;

          console.log(newItem.value);

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
    },
  },
};
</script>

<style scoped>
.container{
  width: 100%;
  height: 100vh; /* 화면의 높이를 100%로 설정 */
  border: 1px solid black;
}
.item{
  width: 100%;
  height: 100vh; /* 화면의 높이를 100%로 설정 */
  border: 1px solid black;
}
.chart-wrapper{
  border: 1px solid red;
  width: 100%;
  height: 50%;
  display: flex;
  justify-content: center;
}
.graph_2{
  border: 1px solid blue;
  width: 50%;
  height: 50%;
  position: relative;
}
.graph_2 > * {
  position: absolute;
  top: 0;
  bottom: 0;
  left: 0;
  right: 0;
}
.line_g{
  border: 1px solid pink;
  width: 100%;
  height: 50%;
  position: relative;
}

</style>