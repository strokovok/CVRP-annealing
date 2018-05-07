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
import moment from 'moment';

window.moment = moment;

export default {
    data() {
        return {
            currentPoints: [],
            bestPoints: [],
            chart: null
        }
    },
    mounted() {
        let ctx = document.getElementById("chart").getContext('2d');
        this.chart = new Chart(ctx, {
            type: 'line',
            data: {
                datasets: [{
                    label: 'Лучший результат',
                    data: this.bestPoints,
                    backgroundColor: 'rgba(0, 0, 0, 0)',
                    borderColor: '#4FC5F7',
                    pointRadius: 0,
                    borderWidth: 1,
                    steppedLine: true
                }, {
                    label: 'Текущий результат',
                    data: this.currentPoints,
                    backgroundColor: 'rgba(0, 0, 0, 0)',
                    borderColor: '#FF6384',
                    pointRadius: 0,
                    borderWidth: 1,
                    steppedLine: true
                }]
            },
            options: {
                devicePixelRatio: 2,
                tooltips: {
                    enabled: false
                },
                scales: {
                    xAxes: [{
                        type: 'time',
                        time: {
                            displayFormats: {
                                'millisecond': 's.SSS[s]',
                                'second': 'm[m] s[s]',
                                'minute': 'h[h] m[m]',
                                'hour': 'h[h]',
                            }
                        },
                        ticks: {
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
        // window.addValuesToChart = this.pushValues;
        let p = [];
        for (let i = 0; i < 1000; ++i)
            p.push({
                x: i * 90,
                y: 5000 / (i / 100 * 25) + Math.random() * 9000 - 4500,
            });
        this.updateChart(p);
    },
    methods: {
        updateChart(points) {
            let cp = this.currentPoints;
            let bp = this.bestPoints;
            while (cp.length > 0)
                cp.pop();
            while (bp.length > 0)
                bp.pop();
            if (points.length === 0) {
                this.chart.update();
                return;
            }
            for (let point of points) {
                point.x = moment(0).add(point.x, 'milliseconds');
                cp.push(point);
                if (bp.length === 0 || bp[bp.length - 1].y > point.y)
                    bp.push(point);
            }
            if (cp[cp.length - 1].x > bp[bp.length - 1].x)
                bp.push({
                    x: cp[cp.length - 1].x,
                    y: bp[bp.length - 1].y
                });
            this.chart.update();
        }
    }
}
</script>