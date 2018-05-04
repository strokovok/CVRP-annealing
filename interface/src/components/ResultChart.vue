<template>
    <div class="chart-container">
        <canvas class="chart" id="chart" width="800" height="208"/>
    </div>
</template>

<style lang="scss" scoped>
    .chart-container {
        transition: all .3s ease;
        transform-origin: 100% 100%;
        &:hover {
            transform: scale(1.412);
            box-shadow: 0 0 10px -1px #FBB150;
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
            chart: null,
            cnt: 0,
            mul: 1,
            buffer: []
        }
    },
    mounted() {
        let ctx = document.getElementById("chart").getContext('2d');
        this.chart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: this.labels,
                datasets: [{
                    label: 'Текущий результат',
                    data: this.values,
                    backgroundColor: 'rgba(0, 0, 0, 0)',
                    borderColor: '#FF6384',
                    pointRadius: 0,
                    borderWidth: 1,
                }]
            },
            options: {
                devicePixelRatio: 2,
                tooltips: {
                    enabled: false
                },
                scales: {
                    xAxes: [{
                        ticks: {
                            maxTicksLimit: 15,
                            fontColor: 'rgba(255, 255, 255, 0.7)'
                        }
                    }],
                    yAxes: [{
                        ticks: {
                            fontColor: 'rgba(255, 255, 255, 0.7)'
                        }
                    }]
                },
                animation: {
                    duration: 0
                },
                legend: {
                    labels: {
                        fontColor: 'rgba(255, 255, 255, 0.7)'
                    }
                }
            }
        });
        setInterval(this.updateChart, 500);
    },
    methods: {
        updateChart() {
            for (let i = 0; i < 10; ++i)
                this.pushValue();
            const mx = 1000;
            if (this.labels.length >= mx && this.labels.length % 3 === 0) {
                for (let i = 0; i < mx; i += 3) {
                    let mn = this.values[i];
                    let mx = this.values[i];
                    for (let j = i; j < i + 3; ++j) {
                        mn = Math.min(mn, this.values[j]);
                        mx = Math.max(mx, this.values[j]);
                    }
                    this.values[i / 3] = mn;
                    this.values[i / 3 + 1] = mx;
                }
                while (this.labels.length > mx / 3) {
                    this.labels.pop();
                    this.values.pop();
                }
            }
            this.chart.update();
        },
        pushValue() {
            this.labels.push(++this.cnt);
            this.values.push((1000 - this.cnt) + Math.random() * 100);
        }
    }
}
</script>