<template>
  <div class="chart-container" ref="container">
    <canvas ref="chart"></canvas>
  </div>
</template>

<script>
import Chart from 'chart.js/auto';

export default {
  name: 'DoughnutChart',
  props: {
    data: {
      type: Object,
      required: true,
    },
  },
  data(){
    return{
      chartOptions: {
        // responsive: false,
        // maintainAspectRatio: false,
        plugins: {
          legend: {
            display: false, // 레전드를 숨김
          },
        },
      }
    }
  },
  mounted() {
    this.renderChart();
  },
  beforeUpdate() {
    if (this.chart) {
      this.chart.destroy();
      this.chart = null;
    }
  },
  beforeDestroy() {
    if (this.chart) {
      this.chart.destroy();
      this.chart = null;
    }
  },
  methods: {
    renderChart() {
      if (this.chart) {
        this.chart.destroy();
      }
      const ctx = this.$refs.chart.getContext('2d');
      this.chart = new Chart(ctx, {
        type: 'doughnut',
        data: this.data,
        options: this.chartOptions,
      });
    },
  },
};
</script>