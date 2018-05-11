<template>
    <div class="progress">
        <div class="ui-label">Прогресс</div>
        <div class="ui-mini-label">{{textStatus}}</div>
        <div class="ui-progress">
            <div class="ui-progress-fill" :style="styleObj"/>
        </div>
    </div>
</template>

<script>
export default {
    computed: {
        beforeProcess() {
            return [
                stateEnum.EMPTY,
                stateEnum.INCORRECT_PROBLEM,
                stateEnum.INCORRECT_SOLUTION,
                stateEnum.PROBLEM_LOADING,
                stateEnum.PROBLEM_READY,
                stateEnum.SOLUTION_LOADING
            ].includes(globalStore.state);
        },
        afterProcess() {
            return [
                stateEnum.SOLUTION_VIEW,
                stateEnum.SOLUTION_SAVING
            ].includes(globalStore.state);
        },
        progress() {
            if (this.beforeProcess)
                return 0;
            if (this.afterProcess)
                return 100;
            return globalStore.stats[statsEnum.PROGRESS] || 0;
        },
        styleObj() {
            return { width: `${this.progress}%` };
        },
        textStatus() {
            if (this.beforeProcess)
                return 'Ожидание';
            if (this.afterProcess)
                return 'Готово!';
            if (globalStore.state === stateEnum.SOLVING)
                return `Выполняется (${this.progress}%)`;
            return `Пауза (${this.progress})`;
        }
    }
}
</script>