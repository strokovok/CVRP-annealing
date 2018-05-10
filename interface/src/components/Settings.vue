<template>
    <div class="settings">
        <div class="ui-label">Настройки</div>
        <div class="settings-list">
            <div class="setting" v-for="setting in settings" :key="setting.key">
                <div class="ui-mini-label">{{setting.label}}</div>
                <div class="setting-control">
                    <button class="ui-trigger"
                            :class="[{'triggered': setting.auto}]"
                            @click="changeAuto(setting.key)">
                        auto
                    </button>
                    <input class="ui-input"
                           :disabled="setting.auto"
                           type="number"
                           @keydown="inputUpdate"
                           v-model="settingsModel[setting.key]">
                </div>
            </div>
        </div>
    </div>
</template>

<style lang="scss" scoped>
    .settings {
        display: flex;
        flex-direction: column;
    }

    .settings-list {
        margin-top: 2px;
        display: flex;
        flex-direction: column;
        max-height: 160px;
        flex-wrap: wrap;
        align-items: flex-start;
    }

    .setting {
        margin-top: 5px;
        &:last-child {
            margin-bottom: 5px;
        }
    }

    .setting-control {
        display: flex;
        .ui-input {
            width: 130px;
            margin-left: 2px;
            margin-right: 6px;
        }
    }
</style>

<script>



export default {
    data() {
        return {
            shit: 55555,
            settings: [{
                label: "Начальная температура",
                key: settingsEnum.T_START,
                auto: true,
            }, {
                label: "Конечная температура",
                key: settingsEnum.T_END,
                auto: true,
            }, {
                label: "Коэффициент охлаждения",
                key: settingsEnum.T_COOLING,
                auto: true,
            }, {
                label: "Количество итераций",
                key: settingsEnum.ITERATIONS,
                auto: false,
            }, {
                label: "Органичение по времени (сек)",
                key: settingsEnum.TIME_LIMIT,
                auto: true,
            }, {
                label: "Мин. задержка итераций (мс)",
                key: settingsEnum.MIN_ITERATION_DELAY,
                auto: true,
            }]
        };
    },
    created() {
        window.globalStore.settings[settingsEnum.ITERATIONS] = 1000000000;
        this.calcAuto();
    },
    computed: {
        settingsModel() {
            return window.globalStore.settings;
        }
    },
    methods: {
        getSetting(key) {
            let index = 0;
            while (this.settings[index].key !== key)
                ++index;
            return this.settings[index];
        },
        changeAuto(key) {
            let setting = this.getSetting(key);
            setting.auto = !setting.auto;
            let tStart = this.getSetting(settingsEnum.T_START);
            let tEnd = this.getSetting(settingsEnum.T_END);
            let tCooling = this.getSetting(settingsEnum.T_COOLING);
            let its = this.getSetting(settingsEnum.ITERATIONS);
            if (!tStart.auto && !tEnd.auto && !tCooling.auto && !its.auto) {
                if (key === settingsEnum.ITERATIONS)
                    tCooling.auto = true;
                else
                    its.auto = true;
            }
            this.calcAuto();
        },
        calcAuto() {
            let tStart = this.getSetting(settingsEnum.T_START);
            let tEnd = this.getSetting(settingsEnum.T_END);
            let tCooling = this.getSetting(settingsEnum.T_COOLING);
            let its = this.getSetting(settingsEnum.ITERATIONS);
            let tl = this.getSetting(settingsEnum.TIME_LIMIT);
            let mindelay = this.getSetting(settingsEnum.MIN_ITERATION_DELAY);
            if (tl.auto)
                globalStore.settings[tl.key] = 100;
            if (mindelay.auto)
                globalStore.settings[mindelay.key] = 0;

            if (its.auto && (tStart.auto || tEnd.auto || tCooling.auto))
                globalStore.settings[its.key] = 1000000000;
            if (tEnd.auto && (tStart.auto || tCooling.auto))
                globalStore.settings[tEnd.key] = 0.1;
            if (tStart.auto && tCooling.auto)
                globalStore.settings[tStart.key] = globalStore.tStartRecommended;

            if (its.auto && !(tStart.auto || tEnd.auto || tCooling.auto)) {
                let start = globalStore.settings[tStart.key];
                let end = globalStore.settings[tEnd.key];
                let cool = globalStore.settings[tCooling.key];
                let val = Math.floor(Math.log(end / start) / Math.log(cool));
                globalStore.settings[its.key] = val;
            }
            if (tEnd.auto && !(tStart.auto || tCooling.auto)) {
                let start = globalStore.settings[tStart.key];
                let cool = globalStore.settings[tCooling.key];
                let val = globalStore.settings[its.key];
                let end = start / Math.pow(cool, -val);
                globalStore.settings[tEnd.key] = end;
            }
            if (tStart.auto && !tCooling.auto) {
                let val = globalStore.settings[its.key];
                let end = globalStore.settings[tEnd.key];
                let cool = globalStore.settings[tCooling.key];
                let start = end * Math.pow(cool, -val);
                globalStore.settings[tStart.key] = start;
            }
            if (tCooling.auto) {
                let val = globalStore.settings[its.key];
                let end = globalStore.settings[tEnd.key];
                let start = globalStore.settings[tStart.key];
                let cool = Math.pow(start / end, -1 / val);
                globalStore.settings[tCooling.key] = cool;
            }
        },
        validateSetting(setting, min, max, normal) {
            let val = globalStore.settings[setting];
            if (isNaN(val))
                val = normal;
            else
                val = parseFloat(val);
            globalStore.settings[setting] = Math.max(min, Math.min(val, max));
        },
        validateSettings() {
            this.validateSetting(settingsEnum.T_START, 10, 1e10, globalStore.tStartRecommended);
            this.validateSetting(settingsEnum.T_END, 0.1, globalStore.settings[settingsEnum.T_START] - 1, 0.1);
            this.validateSetting(settingsEnum.T_COOLING, 0.1, 0.9999, 0.9998);
            this.validateSetting(settingsEnum.ITERATIONS, 1, 1000000000000, 1000000000);
            this.validateSetting(settingsEnum.TIME_LIMIT, 3, 1000000000000, 60);
            this.validateSetting(settingsEnum.MIN_ITERATION_DELAY, 0, 10000, 0);
            this.calcAuto();
        },
        inputUpdate() {
            this.$nextTick(this.validateSettings);
        }
    }
}
</script>