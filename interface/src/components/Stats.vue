<template>
    <div class="stats">
        <div class="stat" v-for="(statVal, statName) in stats" :key="statName">
            <div class="stat-name">{{statName}}</div>
            <div class="stat-value">{{statVal}}</div>
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
            stats: {
                'Примерное время': '25c',
                'Времени прошло': '10c',
                'Итерации': '1232343',
                'Температура': '5555',
                'Лучший результат': '14'
            }
        }
    }
}
</script>