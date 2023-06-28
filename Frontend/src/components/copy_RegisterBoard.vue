<template>
  <div>
    <div class="chart-container">
      <donut-chart :data="chartData1" :options="chartOptions" />
    </div>
    <div class="chart-container">
      <donut-chart :data="chartData2" :options="chartOptions" />
    </div>
  </div>
</template>

<script>
import DonutChart from './DoughnutChart.vue';

export default {
  name: 'App',
  components: {
    DonutChart,
  },
  data() {
    return {
      chartData1: {
        labels: ['Red', 'Blue'],
        datasets: [
          {
            label: 'My First Dataset',
            data: [300, 350-300],
            backgroundColor: ['rgb(255, 99, 132)', 'rgb(54, 162, 235)'],
            hoverOffset: 4,
          },
        ],
      },
      chartData2: {
        labels: ['Green', 'Yellow'],
        datasets: [
          {
            label: 'My First Dataset',
            data: [100, 200],
            backgroundColor: ['rgb(245, 216, 0)', 'rgb(75, 174, 122)'],
            hoverOffset: 4,
          },
        ],
      },
      chartOptions: {
        responsive: true,
        maintainAspectRatio: false,
      },
    };
  },
  // mounted() {
  //   this.$nextTick(() => {
  //     if (this.$refs.chart1 && this.$refs.chart2) {
  //       this.renderCharts();
  //       const canvas1 = this.$refs.donutChart1.$refs.chart;
  //       canvas1.height = canvas1.offsetWidth;
  //       canvas1.width = canvas1.offsetHeight;
  //       const canvas2 = this.$refs.donutChart2.$refs.chart;
  //       canvas2.height = canvas2.offsetWidth;
  //       canvas2.width = canvas2.offsetHeight;
  //     }
  //   });
  // },
  methods: {
    renderCharts() {
      this.renderChart1();
      this.renderChart2();
    },
    renderChart1() {
      const canvas = this.$refs.donutChart1.$refs.chart;
      if (canvas) {
        canvas.getContext('2d').clearRect(0, 0, canvas.width, canvas.height);
        this.$refs.donutChart1.renderChart(this.chartData1, this.chartOptions1);
      }
    },
    renderChart2() {
      const canvas = this.$refs.donutChart2.$refs.chart;
      if (canvas) {
        canvas.getContext('2d').clearRect(0, 0, canvas.width, canvas.height);
        this.$refs.donutChart2.renderChart(this.chartData2, this.chartOptions2);
      }
    },
  },
};
</script>

<style>
.chart-container {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 400px;
}
</style>