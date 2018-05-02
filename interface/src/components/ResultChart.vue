<template>
    <div class="chart-container">
        <canvas class="chart" id="chart" width="800" height="200"/>
    </div>
</template>

<style lang="scss" scoped>
    .chart-container {
        transition: all .3s ease;
        transform-origin: 100% 100%;
        &:hover {
            transform: scale(1.41);
            box-shadow: 0 0 5px 0px white;
        }
    }
</style>

<script>

import Chart from 'chart.js';

export default {
    data() {
        return {
            labels: [],
            values: [],
            chart: null
        }
    },
    mounted() {
        let ctx = document.getElementById("chart").getContext('2d');
        this.chart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: this.labels,
                datasets: [{
                    label: '# of Votes',
                    data: this.values,
                    backgroundColor: 'rgba(0, 0, 0, 0)',
                    borderColor: '#FF6384',
                    pointRadius: 0,
                    borderWidth: 1,
                }]
            },
            options: {
                devicePixelRatio: 1.41,
                tooltips: {
                    enabled: false
                }
            }
        });
        setInterval(this.updateChart, 500);
    },
    methods: {
        updateChart() {
            if (this.labels.length === 1000)
                return;
            this.labels.push(this.labels.length);
            this.values.push((1000 - this.values.length) + Math.random() * 100);
            this.chart.update();
        }
    }
}
</script>