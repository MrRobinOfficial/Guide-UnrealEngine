## 🧠 Multithreading and Asynchronous Tasks

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

The most common way for a game engine to run your gameplay, is simply with a while loop. This pattern is very simple to understand and execute consistently. However, this pattern does not generate the greatest performance benefits. To gain performance, usually you would rewrite your code to be multithreaded.

You can read more about [Game Loop from Robert Nystrom](https://gameprogrammingpatterns.com/game-loop.html).

Ayliroé wrote an awesome documentation on Unreal's multithreading and asynchronous tasks system, which you can read either from [Google Docs](https://docs.google.com/document/d/1uw9Dfui5ZepSrBpMc1DrxFOeRFnDu8ubzFse8Mr_s7E/) or from [Forum Post](https://forums.unrealengine.com/t/multithreading-and-performance-in-unreal/1216417/1).

By the default, Unreal supports multithreading, but only makes partial use of it. While there are dedicated threads for audio, [render](https://docs.unrealengine.com/5.0/en-US/threaded-rendering-in-unreal-engine/) and stats, most operations are still done in the game thread, including EventTicks and Blueprints.

This is why doing expensive calculations in Blueprint will lead to loss of performance. That’s where threading comes in handy!

### Multithreading

Multithreading is the ability of a central processing unit (CPU) (or a single core in a multicore processor) to provide multiple threads of execution concurrently, supported by the operating system. In a multithreaded application, the threads share the resources of a single or multiple cores, which include the computing units, the CPU caches, and the translation lookaside buffer (TLB). This allows for faster speed of computation.

In order to make your game ready for multithreaded, then you're to change your mindset as well. When splitting your code into multiple threads can create [race conditions](https://en.wikipedia.org/wiki/Race_condition), which is when two operations are happening at the same time, and is competing for which one will be the first to execute. This can lead to instability and can cause bugs.

You can read more about [Multithreading from Vulkan Guide](https://vkguide.dev/docs/extra-chapter/multithreading/).

You can also watch a video from [Chris Kanich about deadlocks](https://www.youtube.com/watch?v=oEbXlSH8hyE).

If you want to create multithreading inside Blueprint will minimal C++ code, then here is a [video from Project Ispheria](https://www.youtube.com/watch?v=0Yyh3oQgonI).

### Runnables

`FRunnable` is a class which runs on a dedicated, newly created thread. Which you have full control over it.

They will automatically stop once their work is completed, and are generally useful for big computations that require a nearly continuously running thread.

Here's an example:

```cpp
// .h
#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"

class FMyThread : public FRunnable
{
public:
    FMyThread( /*Parameters*/ )
    {
        bIsRunning = true;
        Thread = FRunnableThread::Create(this, TEXT("MyThread"));
    };

    virtual ~FMyThread()
    {
    	if (Thread)
    	{
            bool bShouldWait = false; // Will forcefully terminate the thread.
    		Thread->Kill(bShouldWait);
    		delete Thread;
    	}
    }

public:
    bool Init() override;
    uint32 Run() override;
    void Exit() override;
    void Stop() override;

private:
    FRunnableThread* Thread;
    bool bIsRunning;
};
```

```cpp
// .cpp
#include "FMyThread.h"

bool FMyThread::Init()
{
    /* Should the thread start? */
    return true;
}

uint32 FMyThread::Run()
{
    while (bIsRunning)
    {
        /* Work on a dedicated thread */
    }

    return 0;
}

void FMyThread::Exit()
{
    /* Post-Run code, threaded */
}

void FMyThread::Stop()
{
    bIsRunning = true;
}
```

When you want to start your thread, include its header and call its constructor (keep the pointer at hand!):

```cpp
auto* Thread = new FMyThread( /*Parameters*/ );
```

### Tasks

[TaskGraph](https://docs.unrealengine.com/5.0/en-US/tasks-systems-in-unreal-engine/), is a job manager that tries to balance out workload along multiple preexisting threads. This is ideal to send packages of small operations, as it abstracts away from you the complexity of managing threads, and also supports defining dependencies between Tasks.

Queuing Tasks will not cause performance concerns due to the threads being already running, but the system may also be less reactive as it has to find slots to fit the work in inside a limited pool, and sending long Tasks should be avoided to not clog-up threads. It may also sometimes decide to run Tasks directly in the game thread, depending on the setup.

#### AsyncTask

If you want to run a small async operation without creating a dedicated class or starting a new thread and do not need the control logic for pausing or callbacks, you can put it inside an `AsyncTask` running on the TaskGraph:

```cpp
AsyncTask(ENamedThreads::AnyHiPriThreadNormalTask, [this] ()
{
    /* Work on the TaskGraph */
    Caller->FunctionToThread(); // Function call captured using [this]
});
```

If you don't know about **lambda**, then highly recommend reading about it on this [section](https://github.com/MrRobinOfficial/Guide-UnrealEngine/#-lambda).

#### ParallelFor

A [fancier](https://isaratech.com/ue4-improving-speed-with-parallelfor/) version of `AsyncTask` that splits a for loop into multiple Tasks running in the TaskGraph.

```cpp
ParallelFor(Array.Num(), [&](int32 i)
{
    // Run Array.Num() operations, with current index i
    /* Work on the TaskGraph (order of execution is variable!) */
    ++Array[i];
});
```

There’s no guarantee about the order or the thread safety of the operation within, so you might want to use mutexes or atomics with it. MSVC has [an analogous](https://learn.microsoft.com/en-us/cpp/preprocessor/loop?view=msvc-170) #pragma loop(hint_parallel(n)). Practically speaking, the contents of your loop must be significant to really benefit from this approach.

#### FNonAbandonableTask

A way to declare your own AsyncTasks, in a format that sits inbetween FRunnable and lambda-like AsyncTasks. You can implement your own code in a standalone class to be more reusable, which will run on the TaskGraph instead of inside a dedicated thread, but missing some of FRunnable’s initializing and stopping logic.

```cpp
#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"

class FMyTask : public FNonAbandonableTask
{
    friend class FAutoDeleteAsyncTask<FMyTask>;

    FMyTask( /*Parameters*/ )
    {
        /* Constructor */
    }

    void DoWork()
    {
        /* Work on the TaskGraph */
    }

    FORCEINLINE TStatId GetStatId() const
    {
        // Probably declares the Task to the TaskGraph
        RETURN_QUICK_DECLARE_CYCLE_STAT(FMyTask, STATGROUP_ThreadPoolAsyncTasks);
    }
};
```

Start your custom Task like such:

```cpp
auto* MyTask = new FAsyncTask<FMyTask>( /*Parameters*/ );
MyTask->StartBackgroundTask();
```

---

As said before, Ayliroé wrote an awesome documentation on Unreal's multithreading and asynchronous tasks system, which you can read either from [Google Docs](https://docs.google.com/document/d/1uw9Dfui5ZepSrBpMc1DrxFOeRFnDu8ubzFse8Mr_s7E/) or from [Forum Post](https://forums.unrealengine.com/t/multithreading-and-performance-in-unreal/1216417/1).
