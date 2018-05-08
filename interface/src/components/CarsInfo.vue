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
    data() {
        return {
            cars: []
        }
    },
    mounted() {
        for (let i = 0; i < 12; ++i)
            this.cars.push({
                cargo: Math.floor(Math.random() * 10000),
                distance: (Math.random() * 10000).toFixed(1)
            });
    }
}
</script>