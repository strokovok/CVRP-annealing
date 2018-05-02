<template>
    <div class="settings">
        <div class="ui-label">Настройки</div>
        <div class="setting" v-for="setting in settings" :key="setting">
            <div class="ui-mini-label">{{setting}}</div>
            <div class="setting-control">
                <button class="ui-trigger">auto</button>
                <input class="ui-input" type="number" v-model="shit">
            </div>
        </div>
    </div>
</template>

<style lang="scss" scoped>
    .settings {
        display: flex;
        flex-direction: column;
    }

    .setting {
        margin-top: 5px;
        &:last-child {
            margin-bottom: 5px;
        }
    }

    .setting-control {
        display: flex;
        .ul-trigger {
            flex-shrink: 0;
        }
        .ui-input {
            flex-basis: 0;
            flex-grow: 1;
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
                "Коэффициент уменьшения температуры",
                "Начальное количество операций на итерацию",
                "Конечное количество операций на итерацию",
                "Коэффициент увеличения количества операций",
                "Количество итераций",
                "Мин. задержка между итерациями",
                "Мин. задержка между перерисовками",
            ]
        };
    }
}
</script>