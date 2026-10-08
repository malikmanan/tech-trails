# 🚀 Self-Hosting LLMs with vLLM

A concise guide on open-weight LLM hosting, continuous request serving, and infrastructure optimizations based on the vLLM engine.

---

## 📌 4-Point Summary

* **The Privacy Advantage:** Self-hosting open-weight models locally ensures that no data leaves your internal infrastructure, making it perfect for secure local testing or sensitive corporate workflows.
* **The Multitasking Bottleneck:** While running a single prompt locally is simple, managing concurrent requests, scheduling active users, and juggling GPU memory bottlenecks across complex multi-step agentic workflows becomes highly inefficient without a dedicated serving framework.
* **vLLM as an Engine:** vLLM solves this by acting as an open-source, high-performance LLM serving engine. It handles incoming connections, maximizes hardware capabilities, and supports new models (like Qwen) right out of the box via Hugging Face.
* **Flexible Deployments:** The engine can be utilized in two distinct ways: running **Offline Inference** directly inside a local Python automation script (ideal for bulk data evaluation), or starting a **Live Web Server** that exposes an OpenAI-compatible API endpoint on a local network.

---

## 🧠 Memory Mind Map

```text
               ┌── Offline Inference (Batch processing inside local script)
               │
[vLLM ENGINE] ─┼── Web API Server (Exposes OpenAI-compatible REST Endpoint)
               │
               │                      ┌── Continuous Batching (Dynamic request slotting)
               └── Core Optimizations ┼── Paged Attention (Block-based KV cache lookup)
                                      └── Prefix Caching & Quantization (Hardware savings)
```

---

## 🛠️ How vLLM Optimizes Infrastructure & Memory

Simply loading raw model weights and running a basic prediction loop causes immediate GPU stalls under multi-user traffic. vLLM bypasses these limitations using two foundational concepts:

### 1. Continuous Batching
* **Traditional Handling:** Standard engines line up requests and bundle them together into a static batch. Everyone must wait for the absolute longest generation to finish before the GPU releases the next set of answers.
* **The vLLM Fix:** It streams data dynamic-iteration style. As soon as a single user's short query finishes generating tokens, vLLM immediately evicts it from the queue and slots a brand new user's incoming request into that active GPU computation step.

### 2. Paged Attention (KV Cache Optimization)
* **The Problem:** During live generation, models store intermediate attention matrices called the **KV Cache** to prevent recalculating old conversation history with every new word. This cache expands drastically with long documents, eating up VRAM.
* **The vLLM Fix:** Inspired by virtual memory operating systems, Paged Attention chops the expanding KV Cache into non-contiguous, uniform physical memory blocks. This completely eliminates memory fragmentation and waste, letting you handle far more concurrent users on a single graphics card.

---

## 💻 Two Ways to Run vLLM

### Mode A: Offline Python Script
Best for background evaluations, classification runs, or dataset annotation where inputs are predefined.

```python
from vllm import LLM, SamplingParams

# Load the framework and configure basic memory boundaries
sampling_params = SamplingParams(temperature=0.7, max_tokens=256)
llm = LLM(model="Qwen/Qwen2.5-7B-Instruct", max_model_len=4096)

prompts = ["Explain LLMs for dummies.", "Write a bash deployment script."]
outputs = llm.generate(prompts, sampling_params)

for output in outputs:
    print(output.outputs[0].text)
```

### Mode B: OpenAI-Compatible Web API Server
Best for live production frontends, external AI agents, and custom chatbots.

```bash
# Start the local engine hosting service via terminal
vllm serve Qwen/Qwen2.5-7B-Instruct --max-model-len 4096
```

Once running on `localhost`, you can target it seamlessly using standard client packages by overriding your base endpoint:

```python
from openai import OpenAI

# Decouples application logic from backend server setup
client = OpenAI(base_url="http://localhost:8000/v1", api_key="local-token")

response = client.chat.completions.create(
    model="Qwen/Qwen2.5-7B-Instruct",
    messages=[{"role": "user", "content": "Explain LLMs for dummies."}]
)
print(response.choices[0].message.content)
```

---
🎬 *Reference link:* [Watch the vLLM Self-Hosting Video Guide](https://youtu.be/OuBxnfPA15g?si=_tTsdo3kJ_CuzBHn)
