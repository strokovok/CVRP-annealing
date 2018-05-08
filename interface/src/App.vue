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
                <routes class="ui-box"/>
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

export default {
    components: {
        Files,
        Settings,
        ProcessControl,
        ResultChart,
        Stats,
        Graph,
        'progress-view': Progress,
        Routes,
        CarsInfo
    }
};
</script>