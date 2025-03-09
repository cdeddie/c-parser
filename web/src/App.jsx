import { useEffect, useState, useRef } from 'react';
import SunSvg from './assets/sun.svg';
import MoonSvg from './assets/moon.svg';
import DiceSvg from './assets/dice.svg';
import './styles/App.css';
import Editor from '@monaco-editor/react';
import createModule from '../main.js';
import Tree from 'react-d3-tree';

const codes = [
`#include <stdio.h>

int main()
{
    printf("Hello world!");
    return 0;
}
`,
`#include <stdio.h>

int main()
{
    int num1 = 5;
    int num2 = 10;
    int sum;
    sum = num1 + num2;
    printf("Sum of %d and %d is: %d", num1, num2, sum);
    return 0;
}
`,
`#include <stdio.h>

int main()
{
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);
    printf("You entered: %d", num);
    return 0;
}
`,
`#include <stdio.h>

void printMessage()
{
    printf("This is a function.");
}

int main()
{
    printMessage();
    return 0;
}
`,
`#include <stdio.h>

int main()
{
    int i;
    for (i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    return 0;
}
`,
`#include <stdio.h>

#define MAX 100
#define MIN 10

int main()
{
    int big_array[MAX];
    int small_array[MIN];
}
`,
`#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int num1 = 5;
    int num2 = 7;
    swap(&num1, &num2);
}
`,
];  

function App() {
  const editorRef = useRef(null);

  function handleEditorDidMount(editor, monaco) {
    editorRef.current = editor;
  }

  const [isDarkMode, setIsDarkMode] = useState(() =>
    window.matchMedia && window.matchMedia('(prefers-color-scheme: dark)').matches
  );
  const [input, setInput] = useState(`#include <stdio.h>

int main() 
{
    return 0;
}`);
  const [output, setOutput] = useState({});
  const [error, setError] = useState(false);
  const [previousIndices, setPreviousIndices] = useState([]);

  function randomInput() {
    let randomIndex;
    do {
      randomIndex = Math.floor(Math.random() * codes.length);
    } while (previousIndices.includes(randomIndex));
  
    setPreviousIndices((prev) => {
      const newHistory = [...prev, randomIndex];
      return newHistory.length > 2 ? newHistory.slice(1) : newHistory;
    });

    if (editorRef.current) {
      editorRef.current.setValue(codes[randomIndex]);
    }
  }

  // WASM STUFF
  const [wasmModule, setWasmModule] = useState(null);

  useEffect(() => {
    createModule().then((Module) => {
      setWasmModule(Module);
    }).catch((error) => {
      console.error("Error creating module:", error);
    });
  }, []);

  function parse() {
    console.log(input);
    if (!wasmModule) {
      console.error("WASM module not loaded yet!");
      setError(true);
      return;
    }
    try {
      const result = wasmModule.run_processing(input);
      const parsedResult = JSON.parse(result);
      setOutput(parsedResult);
      setError(false);
    } catch (error) {
      console.error("Error parsing input:", error);
      setError(true);
    }
  }
  

  useEffect(() => {
    document.documentElement.style.setProperty(
      '--background-color',
      isDarkMode ? '#121212' : '#ffffff'
    );
    document.documentElement.style.setProperty(
      '--text-color',
      isDarkMode ? '#ffffff' : '#000000'
    );
  }, [isDarkMode]);

  const toggleDarkMode = () => {
    setIsDarkMode((prevMode) => !prevMode);
  };

  return (
    <div className="app-container">
      <h1>C Parser</h1>
      <button className="theme-toggle" onClick={toggleDarkMode}>
        <img
          src={isDarkMode ? SunSvg : MoonSvg}
          alt={isDarkMode ? 'Light Mode' : 'Dark Mode'}
          className={isDarkMode ? 'white-svg' : ''}
        />
        {isDarkMode ? 'Switch to Light Mode' : 'Switch to Dark Mode'}
      </button>
      <div className="editor-container">
        <Editor
          height="30vh"
          width="60vw"
          language="c"
          onMount={handleEditorDidMount}
          defaultValue={`#include <stdio.h>

int main() 
{
    return 0;
}`}
          theme={isDarkMode ? 'vs-dark' : 'vs-light'}
          onChange={(value) => setInput(value || '')}
        />
      </div>
      <div className="buttons">
        <button className="parse-button" onClick={parse}>
          <img src="/favicon.svg" className={isDarkMode ? 'white-svg' : ''} alt="parse" />
          Parse
        </button>
        <button onClick={randomInput}><img src={DiceSvg} className={isDarkMode ? 'white-svg' : ''}></img></button>
      </div>
      {error && <div className="error-message">Error parsing, check console.</div>}
      <div className="tree">
        <Tree
          data={output}
          orientation="vertical"
          rootNodeClassName="node__root"
          branchNodeClassName="node__branch"
          leafNodeClassName="node__leaf"
        />
      </div>
    </div>
  );
}

export default App;
