(this.webpackJsonptest=this.webpackJsonptest||[]).push([[0],{12:function(e,t,n){},13:function(e,t,n){},15:function(e,t,n){"use strict";n.r(t);var c=n(1),r=n.n(c),o=n(3),i=n.n(o),s=(n(12),n(4)),j=n(5),l=n(7),a=n(6),u=(n.p,n(13),n(0)),h=n(1),p=(n(3),function(e){Object(l.a)(n,e);var t=Object(a.a)(n);function n(e){var c;return Object(s.a)(this,n),(c=t.call(this,e)).state={employee:{}},c}return Object(j.a)(n,[{key:"componentDidMount",value:function(){var e=this;fetch("/api/employees").then((function(e){return e.json()})).then((function(t){console.log(t),e.setState({employee:t})}))}},{key:"render",value:function(){return Object(u.jsxs)("div",{children:[Object(u.jsx)("h3",{children:"Hello there"}),Object(u.jsx)("table",{children:Object(u.jsx)("tbody",{children:Object(u.jsx)("tr",{children:Object(u.jsx)(b,{employee:this.state.employee})})})})]})}}]),n}(h.Component)),b=function(e){Object(l.a)(n,e);var t=Object(a.a)(n);function n(){return Object(s.a)(this,n),t.apply(this,arguments)}return Object(j.a)(n,[{key:"render",value:function(){return Object(u.jsxs)("tr",{children:[Object(u.jsx)("td",{children:this.props.employee.firstname}),Object(u.jsx)("td",{children:this.props.employee.lastname}),Object(u.jsx)("td",{children:this.props.employee.description})]})}}]),n}(h.Component),d=p,O=function(e){e&&e instanceof Function&&n.e(3).then(n.bind(null,16)).then((function(t){var n=t.getCLS,c=t.getFID,r=t.getFCP,o=t.getLCP,i=t.getTTFB;n(e),c(e),r(e),o(e),i(e)}))};i.a.render(Object(u.jsx)(r.a.StrictMode,{children:Object(u.jsx)(d,{})}),document.getElementById("root")),O()}},[[15,1,2]]]);
//# sourceMappingURL=main.56fba24d.chunk.js.map