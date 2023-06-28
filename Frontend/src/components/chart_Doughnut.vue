<template>
  <canvas ref="chart" />
</template>

<script>
import Chart from 'chart.js/auto';

export default {
  name: 'DonutChart',
  props: {
    data: {
      type: Object,
      required: true,
    },
    options: {
      type: Object,
      default: () => ({}),
    },
  },
  mounted() {
    const chart = new Chart(this.$refs.chart, {
      type: 'doughnut',
      data: this.data,
      options: this.options,
    });
  },
};
</script>