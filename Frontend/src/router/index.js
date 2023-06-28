import Vue from 'vue'
import VueRouter from 'vue-router'
import LoginView from "../views/LoginView.vue"
import MonitorView from "../views/MonitorView.vue"
import RPiView from "../views/RPiView.vue"
import AdminMemView from "../views/AdminMemView.vue"
import AdminHubView from "../views/AdminHubView.vue"
import AdminManView from "../views/AdminManView.vue"
import HubView from "../views/HubView.vue"
import RegisterView from "../views/RegisterView.vue"

Vue.use(VueRouter)

const routes = [
  {
    path: "/",
    name: "Login",
    component: LoginView,
  },
  {
    path: "/monitor",
    name: "Monitor",
    component: MonitorView,
  },
  {
    path: "/monitor/:id",
    name: "Monitor_hub",
    component: HubView,
  },
  {
    path: "/rpi",
    name: "RPi",
    component: RPiView,
  },
  {
    path: "/admin/member",
    name: "AdminMember",
    component: AdminMemView,
  },
  {
    path: "/admin/hub",
    name: "AdminHub",
    component: AdminHubView,
  },
  {
    path: "/admin/manage",
    name: "AdminManage",
    component: AdminManView,
  },
  {
    path: "/register",
    name: "Register",
    component: RegisterView,
  },
  
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

export default router
