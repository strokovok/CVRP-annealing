<template>
    <div class="display-mode">
        <button class="ui-trigger" :class="[{'triggered': onlyBest}]" @click="toggle">
            Отображать только лучший результат
        </button>
    </div>
</template>

<style lang="scss" scoped>
    .display-mode {
        display: flex;
        justify-content: center;
    }
</style>

<script>
export default {
    methods: {
        toggle() {
            window.globalStore.showOnlyBest = !window.globalStore.showOnlyBest;
            eventBus.$emit('redraw');
        }
    },
    computed: {
        onlyBest() {
            return window.globalStore.showOnlyBest;
        }
    }
}
</script>