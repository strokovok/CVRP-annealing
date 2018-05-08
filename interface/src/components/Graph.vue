<template>
    <div class="graph-container">
        <canvas id="graph" class="graph" width="375" height="375"/>
    </div>
</template>

<style lang="scss" scoped>
    .graph-container {
        display: flex;
        justify-content: center;
        align-items: center;
        transition: all .3s ease;
        transform-origin: 100% 0;
        /*<!--&:hover {-->*/
            /*<!--transform: scale(1.66);-->*/
            /*<!--box-shadow: 0 0 10px -1px #FBB150;-->*/
        /*<!--}-->*/
    }

    .graph {
        /*background: #50587C;*/
    }
</style>

<script>
export default {
    data() {
        return {
            vertices: [],
            routes: []
        }
    },
    mounted() {
        let canvas = document.getElementById('graph');
        canvas.width = canvas.height = 375 * 2;
        canvas.style.width = canvas.style.height = '375px';
        canvas.getContext('2d').scale(2, 2);
        this.updateRandomly();
        setInterval(this.updateRoutesRandomly, 1000);
    },
    methods: {
        updateRandomly() {
            let v = [];
            for (let i = 0; i < 40; ++i)
                v.push([
                    (Math.random() - 0.5) * 10000,
                    (Math.random() - 0.5) * 10000
                ]);
            this.updateVertices(v);
        },
        updateRoutesRandomly() {
            let routes = [];
            for (let i = 1; i <= 5; ++i)
                routes.push([i]);
            for (let i = 6; i < 40; ++i)
                routes[Math.floor(Math.random() * 5)].push(i);
            this.updateRoutes(routes);
        },
        updateVertices(v) {
            this.vertices = [];
            let l = v[0][0], r = v[0][0], u = v[0][1], d = v[0][1];
            for (let vert of v) {
                l = Math.min(l, vert[0]);
                r = Math.max(r, vert[0]);
                u = Math.min(u, vert[1]);
                d = Math.max(d, vert[1]);
            }
            let factor = 365 / Math.max(r - l, d - u);
            for (let vert of v)
                this.vertices.push({
                    x: 5 + (vert[0] - l) * factor,
                    y: 5 + (vert[1] - u) * factor
                });
        },
        updateRoutes(routes) {
            this.routes = routes;
            this.redrawGraph();
        },
        redrawGraph() {
            let canvas = document.getElementById('graph');
            let ctx = canvas.getContext('2d');
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            ctx.fillStyle="white";
            ctx.lineWidth = 1.5;
            let edgeColors = ["#10A8AB", "#3469AF", "#4DBFF1", "#E64C66", "#FBB150"];
            let color = 0;
            for (let route of this.routes) {
                color = (color + 1) % edgeColors.length;
                ctx.strokeStyle = edgeColors[color];
                let edges = [];
                for (let i = 1; i < route.length; ++i)
                    edges.push([route[i - 1], route[i]]);
                edges.push([0, route[0]]);
                edges.push([route[route.length - 1], 0]);
                for (let e of edges) {
                    ctx.beginPath();
                    ctx.moveTo(this.vertices[e[0]].x, this.vertices[e[0]].y);
                    ctx.lineTo(this.vertices[e[1]].x, this.vertices[e[1]].y);
                    ctx.stroke();
                }
            }
            for (let v of this.vertices) {
                ctx.beginPath();
                ctx.arc(v.x, v.y, 3, 0, Math.PI * 2, true);
                ctx.fill();
            }
            ctx.beginPath();
            ctx.arc(this.vertices[0].x, this.vertices[0].y, 7, 0, Math.PI * 2, true);
            ctx.fill();
        }
    }
}
</script>