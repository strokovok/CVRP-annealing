<template>
    <div class="process-control">
        <div class="ui-label">Состояние</div>
        <div class="ui-mini-label">Выполняется (50%)</div>
        <div class="ui-mini-label">Температура: 5215</div>
        <div class="ui-mini-label">Операций на итерацию: 12</div>
        <div class="ui-mini-label">Итераций: 120023</div>
        <div class="ui-mini-label">Затраченное время: 11с</div>
        <div class="ui-mini-label">Примерно времени осталось: 9с</div>
        <div class="buttons">
            <button class="ui-button" disabled>Запуск</button>
            <button class="ui-button secondary" disabled>Пауза</button>
            <button class="ui-button danger" disabled>Стоп</button>
        </div>
        <div class="ui-progress">
            <div class="ui-progress-fill"/>
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
        display: flex;
    }

    .ui-progress-fill {
        width: 50%;
    }
</style>