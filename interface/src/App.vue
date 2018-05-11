<template>
    <div class="page">
        <div class="page-column" style="width: 750px">
            <files class="ui-box"/>
            <div class="page-row">
                <settings class="ui-box" style="width: 470px"/>
                <stats class="ui-box"/>
            </div>
            <div class="page-row">
                <process-control class="ui-box"/>
                <progress-view class="ui-box" style="width: 450px"/>
            </div>
            <result-chart class="ui-box"/>
            <cars-info class="ui-box"/>
            <div class="page-row" style="align-items: flex-start">
                <div class="page-column">
                    <display-mode class="ui-box"/>
                    <routes class="ui-box"/>
                </div>
                <graph class="ui-box" style="margin-bottom: 100px"/>
            </div>
        </div>
    </div>
</template>

<style lang="scss" scoped>
    .page {
        margin: 5px 0;
        width: 100%;
        display: flex;
        justify-content: center;
        align-items: flex-start;
        .page-column {
            display: flex;
            flex-direction: column;
        }
        .page-row {
            display: flex;
        }
    }
</style>

<script>

import Files from './components/Files.vue';
import Settings from './components/Settings.vue';
import ProcessControl from './components/ProcessControl.vue';
import ResultChart from './components/ResultChart.vue';
import Stats from './components/Stats.vue';
import Graph from './components/Graph.vue';
import Progress from './components/Progress.vue';
import Routes from './components/Routes.vue';
import CarsInfo from './components/CarsInfo.vue';
import DisplayMode from './components/DisplayMode.vue';

window.stateEnum = {
    EMPTY: 'EMPTY',
    PROBLEM_LOADING: 'PROBLEM_LOADING',
    INCORRECT_PROBLEM: 'INCORRECT_PROBLEM',
    PROBLEM_READY: 'PROBLEM_READY',
    SOLVING: 'SOLVING',
    PAUSED: 'PAUSED',
    SOLUTION_LOADING: 'SOLUTION_LOADING',
    INCORRECT_SOLUTION: 'INCORRECT_SOLUTION',
    SOLUTION_VIEW: 'SOLUTION_VIEW',
    SOLUTION_SAVING: 'SOLUTION_SAVING'
};

window.settingsEnum = {
    T_START: 'T_START',
    T_END: 'T_END',
    T_COOLING: 'T_COOLING',
    ITERATIONS: 'ITERATIONS',
    TIME_LIMIT: 'TIME_LIMIT',
    MIN_ITERATION_DELAY: 'MIN_ITERATION_DELAY'
};

window.statsEnum = {
    ESTIMATED_TIME: 'ESTIMATED_TIME',
    TIME_PASSED: 'TIME_PASSED',
    ITERATIONS: 'ITERATIONS',
    TEMPERATURE: 'TEMPERATURE',
    BEST_RESULT: 'BEST_RESULT',
    PROGRESS: 'PROGRESS'
};

export default {
    data() {
        return {
            store: {
                state: stateEnum.EMPTY,
                settings: {},
                stats: {},
                currentCars: [],
                bestCars: [],
                currentRoutes: [],
                bestRoutes: [],
                graph: [],
                chart: [],
                averageOpTime: 1 / 50,
                tStartRecommended: 5000,
                showOnlyBest: false,
                file: ""
            }
        }
    },
    created() {
        window.globalStore = this.store;
        window.handleAppEvent = this.handleAppEvent;
    },
    methods: {
        handleAppEvent(event) {
            let newState = event.newState;
            let update = event.update;
            if (newState)
                this.store.state = newState;
            if (update) {
                for (let arrName of ['currentCars', 'bestCars', 'chart', 'currentRoutes', 'bestRoutes', 'graph'])
                    if (update.hasOwnProperty(arrName)) {
                        while (this.store[arrName].length > 0)
                            this.store[arrName].pop();
                        for (let item of update[arrName])
                            this.store[arrName].push(item);
                    }
                if (update.hasOwnProperty('file'))
                    this.store.file = update.file;
                if (update.hasOwnProperty('averageOpTime'))
                    this.store.averageOpTime = update.averageOpTime;
                if (update.hasOwnProperty('tStartRecommended'))
                    this.store.tStartRecommended = update.tStartRecommended;
                if (update.hasOwnProperty('stats'))
                    for (let stat in update.stats)
                        this.store.stats[stat] = update.stats[stat];
            }
            window.eventBus.$emit('redraw');
        }
    },
    components: {
        Files,
        Settings,
        ProcessControl,
        ResultChart,
        Stats,
        Graph,
        'progress-view': Progress,
        Routes,
        CarsInfo,
        DisplayMode
    }
};
</script>