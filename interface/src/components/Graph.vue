<template>
    <div class="graph-container">
        <canvas class="graph" width="526" height="341"/>
    </div>
</template>

<style lang="scss" scoped>
    .graph-container {
        display: flex;
        justify-content: center;
        align-items: center;
        transition: all .3s ease;
        transform-origin: 100% 0;
        &:hover {
            transform: scale(1.66);
            box-shadow: 0 0 10px -1px #FBB150;
        }
    }

    .graph {
        background: #50587C;
    }
</style>