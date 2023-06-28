<template>
  <div class="chart-container" ref="container">
    <canvas ref="lineChart" height="70"></canvas>
  </div>
</template>

<script>
import Chart from 'chart.js/auto';

export default {
  name: 'LineChart',
  props: {
    chartData: {
      type: Object,
      required: true,
    },
    chartOptions: {
      type: Object,
      default: () => ({
        plugins:{
          legend:{
            display: false
          }
        },
      }),
    },
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
        this.chart.data.datasets = this.chartData.datasets;
        this.chart.update();
        return;
      }

      const canvas = this.$refs.lineChart;
      this.chart = new Chart(canvas, {
        type: 'line',
        data: this.chartData,
        options: this.chartOptions,
      });
    },
  },
};
</script>