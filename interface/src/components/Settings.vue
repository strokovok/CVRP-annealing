<template>
    <div class="settings">
        <div class="ui-label">Настройки</div>
        <div class="settings-list">
            <div class="setting" v-for="setting in settings" :key="setting">
                <div class="ui-mini-label">{{setting}}</div>
                <div class="setting-control">
                    <button class="ui-trigger">auto</button>
                    <input class="ui-input" type="number" v-model="shit">
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
            settings: [
                "Начальная температура",
                "Конечная температура",
                "Коэффициент охлаждения",
                "Количество итераций",
                "Органичение по времени (сек)",
                "Мин. задержка итераций (мс)",
            ]
        };
    }
}
</script>