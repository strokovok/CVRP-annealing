<template>
    <div class="cars-info">
        <div class="labels">
            <div class="label">Машина</div>
            <div class="label">Груз</div>
            <div class="label">Путь</div>
        </div>
        <div class="labels" v-for="(car, i) in cars" :key="i">
            <div class="label">{{i}}</div>
            <div class="label">{{car.cargo}}</div>
            <div class="label">{{car.distance}}</div>
        </div>
    </div>
</template>

<style lang="scss" scoped>
    .cars-info {
        display: flex;
        justify-content: space-between;
        overflow-x: auto;
    }

    .labels {
        display: flex;
        flex-direction: column;
        align-items: center;
    }

    .label {
        margin: 5px;
        font-size: 12px;
        color: white;
    }
</style>

<script>
export default {
    computed: {
        cars() {
            if (![
                stateEnum.SOLUTION_VIEW,
                stateEnum.SOLVING,
                stateEnum.PAUSED,
                stateEnum.SOLUTION_SAVING
            ].includes(window.globalStore.state))
                return [];
            if (window.globalStore.showOnlyBest)
                return window.globalStore.bestCars;
            return window.globalStore.currentCars;
        }
    }
}
</script>