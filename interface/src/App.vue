<template>
    <div class="page">
        <div class="page-column">
            <files class="ui-box"/>
            <settings class="ui-box"/>
        </div>
        <div class="page-column">
            <process-control class="ui-box"/>
            <result-chart class="ui-box"/>
        </div>
    </div>
</template>

<style lang="scss" scoped>
    .page {
        margin-top: 5px;
        width: 100%;
        display: flex;
        justify-content: center;
        align-items: flex-start;
        .page-column {
            display: flex;
            flex-direction: column;
        }
    }
</style>

<script>

import Files from './components/Files.vue';
import Settings from './components/Settings.vue';
import ProcessControl from './components/ProcessControl.vue';
import ResultChart from './components/ResultChart.vue';

export default {
    components: {
        Files,
        Settings,
        ProcessControl,
        ResultChart
    }
};
</script>