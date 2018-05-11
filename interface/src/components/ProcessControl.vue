<template>
    <div class="process-control">
        <div class="ui-label">Управление</div>
        <div class="buttons">
            <button class="ui-button" :disabled="!launchAbility" @click="launchSolve">Запуск</button>
            <button class="ui-button secondary" :disabled="!pauseAbility" @click="pauseSolve">Пауза</button>
            <button class="ui-button danger" :disabled="!stoppingAbility" @click="stopSolve">Стоп</button>
        </div>
    </div>
</template>

<style lang="scss" scoped>
    .process-control {
        display: flex;
        flex-direction: column;
        align-items: flex-start;
    }

    .buttons {
        flex-shrink: 0;
        display: flex;
    }
</style>

<script>
export default {
    methods: {
        launchSolve() {
            if (window.requestLaunchSolve) {
                window.handleAppEvent({ newState: stateEnum.SOLVING, update: {
                        currentRoutes: [],
                        bestRoutes: [],
                        currentCars: [],
                        bestCars: [],
                        chart: [],
                        stats: {
                            [statsEnum.PROGRESS]: 0
                        }
                    }});
                window.requestLaunchSolve(window.globalStore.settings);
            }
        },
        pauseSolve() {
            if (window.requestPauseSolve) {
                window.handleAppEvent({ newState: stateEnum.PAUSED });
                window.requestPauseSolve();
            }
        },
        stopSolve() {
            if (window.requestStopSolve) {
                window.handleAppEvent({ newState: stateEnum.PROBLEM_READY });
                window.requestStopSolve();
            }
        }
    },
    computed: {
        launchAbility() {
            return [
                stateEnum.PROBLEM_READY,
                stateEnum.SOLUTION_VIEW,
                stateEnum.INCORRECT_SOLUTION
            ].includes(globalStore.state);
        },
        pauseAbility() {
            return globalStore.state === stateEnum.SOLVING;
        },
        stoppingAbility() {
            return [
                stateEnum.SOLVING,
                stateEnum.PAUSED
            ].includes(globalStore.state);
        }
    }
}
</script>