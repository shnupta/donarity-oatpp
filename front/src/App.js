import logo from './logo.svg';
import './App.css';
const React = require('react'); // <1>
const ReactDOM = require('react-dom'); // <2>

const fetchData = () => {
    return fetch("/api/employees")
        .then((response) => response.json());}

class App extends React.Component {
    constructor(props) {
        super(props);
        this.state = {employee: {}};
    }

    componentDidMount() { // <2>
        fetchData().then(response => {
            console.log(response);
            this.setState({employee: response});
        });
    }

    render() { // <3>
        return (
            <div>
                <h3>Hello there</h3>
                <table>
                    <tbody>
                    <tr>
                        <Employee employee={this.state.employee}/>
                    </tr>
                    </tbody>
                </table>
            </div>
        )
    }
}

class Employee extends React.Component{
    render() {
        return (
            <tr>
                <td>{this.props.employee.firstname}</td>
                <td>{this.props.employee.lastname}</td>
                <td>{this.props.employee.description}</td>
            </tr>
        )
    }
}

// function App() {
//   return (
//     <div className="App">
//       <header className="App-header">
//         <img src={logo} className="App-logo" alt="logo" />
//         <p>
//           Edit <code>src/App.js</code> and save to reload.
//         </p>
//         <a
//           className="App-link"
//           href="https://reactjs.org"
//           target="_blank"
//           rel="noopener noreferrer"
//         >
//           Learn React
//         </a>
//       </header>
//     </div>
//   );
// }

export default App;
