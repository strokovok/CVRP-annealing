<template>
    <div class="files">
        <div class="ui-label">Проверка файла</div>
        <div class="buttons">
            <button class="ui-button">Загрузить</button>
            <button class="ui-button" disabled>Сохранить</button>
            <button class="ui-button danger" disabled>Сброс</button>
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

    }
};
</script>