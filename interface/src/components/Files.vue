<template>
    <div class="files">
        <div class="ui-label">{{status}}</div>
        <div class="buttons">
            <button class="ui-button" :disabled="!problemLoadAbility" @click="loadProblem">
                Загрузить задачу
            </button>
            <button class="ui-button" :disabled="!solutionLoadAbility" @click="loadSolution">
                Загрузить решение
            </button>
            <button class="ui-button secondary" :disabled="!solutionSaveAbility" @click="saveSolution">
                Сохранить решение
            </button>
            <button class="ui-button danger" :disabled="!solutionResetAbility" @click="resetSolution">
                Сброс решения
            </button>
        </div>
    </div>
</template>

<style lang="scss" scoped>
    .files {
        display: flex;
        flex-direction: column;
        align-items: flex-start;
    }

    .buttons {
        display: flex;
    }
</style>

<script>

export default {
    methods: {
        loadProblem() {
            if (window.requestProblemLoading)
                window.requestProblemLoading();
        },
        loadSolution() {
            if (window.requestSolutionLoading)
                window.requestSolutionLoading();
        },
        saveSolution() {
            if (window.requestSolutionSaving)
                window.requestSolutionSaving();
        },
        resetSolution() {
            window.handleAppEvent({ event: eventsEnum.SOLUTION_RESET });
        }
    },
    computed: {
       status() {
           return {
               [stateEnum.EMPTY]: 'Загрузите задачу',
               [stateEnum.PROBLEM_LOADING]: 'Проверка задачи',
               [stateEnum.INCORRECT_PROBLEM]: 'Некорректный файл задачи',
               [stateEnum.PROBLEM_READY]: 'Задача загружена',
               [stateEnum.SOLVING]: 'Идёт решение',
               [stateEnum.PAUSED]: 'Решение на паузе',
               [stateEnum.SOLUTION_VIEW]: 'Просмотр решения',
               [stateEnum.SOLUTION_LOADING]: 'Проверка решения',
               [stateEnum.INCORRECT_SOLUTION]: 'Некорректный файл решения',
               [stateEnum.SOLUTION_SAVING]: 'Сохранение решения'
           }[globalStore.state];
       },
       problemLoadAbility() {
           return [
               stateEnum.EMPTY,
               stateEnum.INCORRECT_PROBLEM,
               stateEnum.PROBLEM_READY,
               stateEnum.SOLUTION_VIEW,
               stateEnum.INCORRECT_SOLUTION
           ].includes(globalStore.state);
       },
       solutionLoadAbility() {
           return [
               stateEnum.PROBLEM_READY,
               stateEnum.SOLUTION_VIEW,
               stateEnum.INCORRECT_SOLUTION
           ].includes(globalStore.state);
       },
       solutionSaveAbility() {
           return globalStore.state === stateEnum.SOLUTION_VIEW;
       },
       solutionResetAbility() {
           return [
               stateEnum.INCORRECT_SOLUTION,
               stateEnum.SOLUTION_VIEW
           ].includes(globalStore.state);
       }
    }
};
</script>