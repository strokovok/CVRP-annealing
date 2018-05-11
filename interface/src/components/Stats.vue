<template>
    <div class="stats">
        <div class="stat" v-for="stat in stats" :key="stat.key">
            <div class="stat-name">{{stat.label}}</div>
            <div class="stat-value">{{statsVals[stat.key]}}{{statsVals[stat.key] != '-' ? stat.prefix : ''}}</div>
        </div>
    </div>
</template>

<style lang="scss" scoped>
    .stats {
        display: flex;
        flex-direction: column;
        color: transparentize(white, 0.1);
        font-size: 13px;
        padding: 3px !important;
        min-width: 240px;
    }

    .stat {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding: 12px 15px;
        &:not(:first-child) {
            border-top: 1px solid #2E3758;
        }
    }

    .stat-value {
        font-size: 14px;
    }
</style>

<script>

export default {
    data() {
        return {
            stats: [{
                label: 'Примерное время',
                key: statsEnum.ESTIMATED_TIME,
                prefix: 'с'
            }, {
                label: 'Времени прошло',
                key: statsEnum.TIME_PASSED,
                prefix: ''
            }, {
                label: 'Итерации',
                key: statsEnum.ITERATIONS,
                prefix: ''
            }, {
                label: 'Температура',
                key: statsEnum.TEMPERATURE,
                prefix: ''
            }, {
                label: 'Лучший результат',
                key: statsEnum.BEST_RESULT,
                prefix: ''
            }]
        }
    },
    created() {
        for (let stat in statsEnum)
            this.$set(globalStore.stats, stat, '-');
    },
    computed: {
        statsVals() {
            let res = JSON.parse(JSON.stringify(globalStore.stats));
            if ([
                stateEnum.EMPTY,
                stateEnum.PROBLEM_LOADING,
                stateEnum.INCORRECT_PROBLEM,
                stateEnum.PROBLEM_READY,
                stateEnum.SOLUTION_LOADING,
                stateEnum.INCORRECT_SOLUTION
            ].includes(globalStore.state)) {
                res[statsEnum.TIME_PASSED] = "-";
                res[statsEnum.ITERATIONS] = "-";
                res[statsEnum.TEMPERATURE] = "-";
                res[statsEnum.BEST_RESULT] = "-";
            }
            if (![
                stateEnum.PROBLEM_READY,
                stateEnum.INCORRECT_SOLUTION,
                stateEnum.SOLUTION_VIEW,
                stateEnum.SOLVING,
                stateEnum.PAUSED,
            ].includes(globalStore.state))
                res[statsEnum.ESTIMATED_TIME] = "-";
            for (let key in res)
                if (!isNaN(res[key]))
                    res[key] = Math.round(parseFloat(res[key]) * 100) / 100;
            return res;
        }
    }
}
</script>