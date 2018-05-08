<template>
    <div class="process-control">
        <div class="ui-label">Управление</div>
        <div class="buttons">
            <button class="ui-button" disabled>Запуск</button>
            <button class="ui-button secondary" disabled>Пауза</button>
            <button class="ui-button danger" disabled>Стоп</button>
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