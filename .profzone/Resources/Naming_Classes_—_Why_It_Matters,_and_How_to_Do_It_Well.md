
# Naming Classes — Why It Matters, and How to Do It Well

#### Author: Anastasiia Zhuravleva

September 10, 2018

<img src="https://www.nutrient.io/_astro/preview.whFF-E4v_PBLpp.png">

Let’s talk about naming things when coding, why it matters, and how to get better at it. For the sake of simplicity, I will use the word “class” throughout this post to describe naming targets, but this doesn’t mean I’m excluding other entities like interfaces, enums, etc.


## Why Naming Matters

Here are some of the benefits of proper class naming and naming conventions:

* You know what to expect from a certain class without looking at code or documentation, even if you aren’t the person who created it or if it was written a long time ago.
* It’s easy to search and navigate a codebase.
* It’s easier to talk to your team when discussing problems/improvements.
* It makes onboarding newcomers easier, quicker, and less confusing.

A properly used MVP with an established naming convention is usually a good example of working naming expectations. If the class is named `UseCase/Interactor`, you’d expect it to contain business logic. But let’s say that we have a convention to use `UseCase` for a single piece of logic and `Interactor` to put in similar `UseCase`s.

Let’s also pretend we have a catalog application about all different kinds of monsters. You can have your own collection of monsters you have encountered, add them to favorites, and keep track of limited edition monsters. By combining those two knowledge aspects (MVP + the monster app), you can tell, without even checking inside that:

`GetAllMonstersUseCase` — returns a collection of all monsters. `GetMonsterByIdUseCase` — requires that you pass an ID to get a `Monster`.

And if you find `MonsterFilteringInteractor`, you shouldn’t be surprised to find methods such as `getMonstersForArea(area)` or `getMonstersLargerThen(size)` inside of it.

Now imagine you are looking for a method, which, for example, returns all carnivorous monsters. To do this, check in the filtering interactor, and if this method doesn’t exist, you will at least have a nice idea about where the proper place to add it is.

Enough explanation for now; let’s get to the naming itself, along with some important tips to keep in mind.

## If It Makes No Sense, Remove It

This is the general rule of thumb. If a word is ambiguous, doesn’t add any meaning to a name, and is not the part of established naming convention, then just delete this word.

Let’s look at a simple example.

`SpecialMonsterView` — What is so special about this view or these `Monster`s? We aren’t even sure to which noun this special word belongs. Delete the `Special` part and you will be left with `MonsterView`, which gives us an idea that this view will show monsters in some way, but it is still a vague naming. Now let’s check inside, because the way this view was named before forces us to do so. Ask yourself what this view shows and what the word special might have referred to. Some options could be:

* Favorite monsters for users — `FavoriteMonsterView`.
* Recommendations for the user to check on these monsters because of the difficulty scaling — `RecommendedMonsterView`.
* Monsters that will appear only for a short time or during some event — `EventMonsterView`.

And so on. You get the idea.

## Ask What/How/Where?

Asking yourself these three questions will also help you come up with a good name. For example:

* What exactly does this class do?
* How exactly does it perform a certain task?
* Is there something specific about its location?

Here is an example:

Let’s say we have a `MonsterRepository` interface, which should provide us with some basic operations for monsters, such as creating new monsters, getting all monsters, and getting monsters by ID.

In such a case, here are your possible naming examples for implementations, along with a description of what they are used for:

* `InMemoryMonsterRepository` — contains a hardcoded collection of monsters to retrieve and add to. This is useful for testing or when the implementation details aren’t decided yet but you can already start developing the rest using the “dummy” monster data.
* `NetworkMonsterRepository` — tells you that this repository needs a network connection and works with the data from the server.
* `CachedNetworkMonsterRepository` — this is not just using the networking, but it also performs some sort of caching, and you can expect that it is capable of retrieving at least some monster data when offline if it had a chance to cache it earlier.
* `DBFlowMonsterRepository`, `RoomMonsterRepository`, `SQLiteMonsterRepository` or `RealmMonsterRepository` — tell us that a repository was implemented using a specific library.

## Conventions Are Important

Naming conventions are important, and following them precisely is important as well.

If you have a greenfield project, you should think about the architecture you want to try out, and then come up with the initial naming structure. Jot down some ideas and present them to your team. Or, if you are working alone, take a good look at what you came up with and check the internet for more ideas. You might even want to put the results of your brainstorming on Stack Exchange to get some advice.

If you are joining an already existing project, ask the following questions:

* What are already existing conventions?
* How well were they followed?
* Are there some places that are still following some outdated conventions or no convention at all (and ideally need to be refactored)?

If you decide to change the naming convention, check to see how hard it will be to convert the old code to it as well. If it just affects the naming, most modern IDEs offer an easy rename option. But if the naming convention change involves architecture changes as well, think about how hard it will be to migrate old classes in order for them to fit in the new convention. Then, if you can, refactor. If not, you should at least write comments about your thoughts on the needed refactoring.

## What If You Don’t Know the Function/Purpose Yet?

If you only have a vague idea about what a class is going to be doing when you start to work on it and have a hard time coming up with any name, just call it something ridiculous to remind yourself later that the name needs to be changed. And by ridiculous I don’t mean some vague name like `Manager` or `Handler`; just call it `Dolphin` or `Penguin` or `Fairy` or whatever weird and unrelated name that comes into your mind. It should be strange enough for you to not be tempted to keep it. Later on, when that class is written, it will be easier to give it a proper name.

## It Is Easy to Name If You Have a Class That Does One Thing

If, while asking yourself what/how/where questions, you came up with too many `and`s in your answer, that probably means that a class is doing too much and you should refactor it into smaller classes until you reach the point where you will be able to properly name each of them.

Here is an example:

This class will provide you with special edition (SE) monsters *and* allow you to purchase those SE bundles *and* tell you if the promotion video should be shown when you attempt to buy *and* check for an internet connection because we need to make sure that this SE content is still active *and* allow you to submit a suggestion for the concept of the next SE monster *and* give you an option to leave a feedback about the recent SE.

Now let’s take a look at this class and cram in as much logic as possible:

```cpp
/**

* It is also called Manager because it does too much and everybody is calling these kinds of classes managers.

*/

class SpecialEditionManager() {

/**

* Checks that the bundle isn't purchased yet and attempts the purchase.

* Shows the "thanks for purchase" message after the successful purchase or error.

*/

fun purchase(){

// A lot of code.

...

}

/**

* Checks for internet connection and possibly things like the type of the network

* (mobile/Wi-Fi) or the servers to ensure the SE content is working // and so on.

*/

fun checkConnection() : Boolean {

// Also a lot of code.

...

}

/**

* Code that requests monsters from the servers and parses it to our

* monster models and does sorting or some other processing.

*/

fun getMonsters() : List<Monster>{

// You get the idea about a lot of code.

...

}

/**

* Checks that the submitted monster has all properties set correctly and that said monster

* doesn't already exist, and then converts this monster to what's required by the server format

* and sends it out.

*/

fun submitMonster(monster: Monster){

...

}

/**

* Checks if it is the first two weeks of a SE, requests the current promo video, and creates the

* view to show the promo.

*/

fun showPromo(){

...

}

/**

* Checks that the user is logged in, all contact information is correct, the internet

* connection is available, and there is a server available to receive this feedback.

*/

fun sendFeedback(feedback: Feedback){

...

}

}
```

Just imagine how big this class will end up with all of this logic and how hard it is going to be to debug, test, expand, and try to fix something while not breaking the other functionality. Obviously, you will have a hard time naming something like this.

In general, the refactoring will require all of the functionalities described above to be extracted to smaller classes with proper names.

In the end, our `SpecialEditionManager` becomes the following:

* The class that checks on connectivity. Name variants are: `Connectivity`, `ConnectionChecker`, `ConnectivityProvider`.
* `FeedbackSender` will verify and send feedback and will have the `Connectivity` dependency to get networking info.
* The entire monster showing and submitting part can be split into some sort of architectural decision, and for an MVP example, it can become `SpecialEditionInteractor` or a use case combo such as `GetSpecialEditionMonstersUseCase` and `SubmitSpecialEditionMonsterUseCase` followed by `SpecialEditionPresenter` and the multiple views `SpecialEditionMonstersCollectionView`, `SpecialEditionPromoView`, `SpecialEditionMonsterSubmissionView`, and `SpecialEditionFeedbackView`. Notice that the words `UseCase`, `Interactor`, `View`, and `Presenter` will be subjects of the team naming convention described before. Even though these words can still be considered vague, they should have a conventional weight behind them.
* `SpecialEditionBilling` will perform the entire purchase part and provide info on already purchased bundles.

As a result, you will end up with at least six smaller classes after such a refactoring, which will do less, contain scoped logic, and be much easier to name.

## More Words != Better Naming

Using more words to name a single class might sound like a good way to describe what it does, especially after I mentioned `GetSpecialEditionMonstersUseCase`, but more words don’t always make more sense.

For example, consider `SpecialViewingCaseMonsterManagerEventsHandlerActivitySingleton`. It has eight words in its name, but the only words that convey any meaning are:

* `Monster` — since it is one of the models.
* `Singleton` (with the `Activity` scope?) — since it tells us that either it is written that way so you can have only one instance of it at a time, or that the author of this class wanted to convey that intent, but there is nothing preventing you from creating another instance of it.

Notice how the rest of words provide us only with general abstractions, like `Viewing` or `Special`, and the rest of words tell us nothing at all (I’m looking at you, `ManagerListener`).

After checking on what is inside (because again, the naming forced us to do this), we find:

* `SpecialViewingCaseMonster` — shows us the connection to the `SpecialMonsterView` from before.
* `EventsHandler` — after checking what events it handles, it turns out it is about responding to view click events.
* `Manager` — it turns out that the class does a job of presenter and combines/provides the state for our `FavoriteMonsterView`.
* `ActivitySingleton` — the codebase utilizes some sort of dependency injection and the author wanted to make sure this class will be an activity scoped singleton.

Let’s refactor the name to a proper one:

* `SpecialViewingCaseMonster` — Let’s say that it was all about favorite monsters and convert that part to `FavoriteMonster`.
* `EventsHandler` and `Manager` — These two names are talking about the presenter’s job, but most likely in a non-conventional way. After talking with the team, you discover this class was written when they just started to try the MVP out and now they call them presenters, so let’s change it to `Presenter`.
* `ActivitySingleton` — This was added because the team had started introducing dependency injection and it was “the new thing to try out,” but the convention hadn’t been formed yet, thereby leading to this naming addition. Once everybody is comfortable with dependency injection, this part can simply be removed, or you can add it to documentation for this class.

Now `SpecialViewingCaseMonsterManagerEventsHandlerActivitySingleton` becomes `FavoriteMonsterPresenter`, and thanks to naming conventions inside the team, you know what this class is all about.

## Talk to Your Team about Naming

If you’ve considered all the previous sections but are still unable to pick the right name, just discuss it with your team. If you have few names that you think are maybe OK but you are still not sure, add them to the discussion as well. And don’t forget to mention why you think a certain entity should be named a particular way. The feedback and input from someone else is helpful in deciding on a new name.

## Use Documentation to Describe Small Details

If you still want to add more details to help other people understand what the purpose of a particular class is, use comments/documentation. Treat the class documentation as a second source of information that wasn’t important enough to end up in the class name. This can include:

* Dependency injection details — The `ActivitySingleton` naming part from the previous section should end up in class documentation if you still think it’s worth mentioning.
* Refactoring plans — If you have done some refactoring research on the old class but didn’t manage to perform the refactoring, just leave the information as a starting point for a future coder.
* Hidden dependencies — Some older classes might have hidden dependencies leading to unexpected results. Those hidden dependencies are better off being refactored as well, but for now, you can at least describe them in comments.
* Any other details you can think of that would be nice to mention but are too long to put in a class name.

## What Is Wrong with Manager Though?

The short answer is nothing. The long answer is nothing is wrong with the word itself, and you can use it if you have a proper convention, since it is still a vague word. But you must know what to expect from a class named `Manager` without looking at its contents — not just that it “manages” something. You can use this word to replace the term “presenter” in MVP if you like. The problem is how overused and smelly this word has become in the coding world because it is used to name classes that are doing too much stuff and usually consist of more than 1,000 lines of code.

## Conclusion

Picking names of classes is not always easy, but hopefully these tips have given you a good starting point. For more on this topic, you might want to read Simone’s article, [Naming Is Hard — Difficulties of Naming Variables](https://www.nutrient.io/blog/naming-is-hard/).

## FAQ

Why is naming classes important in software development?

Naming classes is crucial because it enhances code readability, maintainability, and understanding for developers. Well-named classes clearly convey their purpose and functionality, making collaboration easier.

What are the best practices for naming classes in programming?

Best practices include:

* Using descriptive names.
* Following consistent naming conventions.
* Avoiding abbreviations.
* Ensuring names reflect the class’s role and behavior within the application.

How do poor class names affect software projects?

Poor class names can lead to confusion, increased development time, and bugs due to misunderstandings about a class’s purpose, which negatively impacts code quality and team productivity.

Can class names impact code readability and maintainability?

Yes, well-chosen class names significantly improve code readability and maintainability by making it easier for developers to understand the codebase, navigate through classes, and make changes efficiently.

What strategies can help improve class naming in large projects?

Strategies include:

* Establishing naming guidelines.
* Conducting code reviews.
* Using domain-specific language.
* Regularly refactoring to improve names as the project evolves and new requirements arise.

![Anastasiia Zhuravleva](./Naming Classes — Why It Matters, and How to Do It Well_files/steffen.DzCEIadE_ZtdiTG.jpg)

#### Anastasiia Zhuravleva

#### Explore related topics

[Tips](https://www.nutrient.io/blog/tags/tips/)   [Development](https://www.nutrient.io/blog/tags/development/)

Why Naming Matters   Table of contents

## Table of contents

* [Why Naming Matters](https://www.nutrient.io/blog/naming-classes-why-it-matters-how-to-do-it-well/#why-naming-matters)
* [If It Makes No Sense, Remove It](https://www.nutrient.io/blog/naming-classes-why-it-matters-how-to-do-it-well/#if-it-makes-no-sense-remove-it)
* [Ask What/How/Where?](https://www.nutrient.io/blog/naming-classes-why-it-matters-how-to-do-it-well/#ask-whathowwhere)
* [Conventions Are Important](https://www.nutrient.io/blog/naming-classes-why-it-matters-how-to-do-it-well/#conventions-are-important)
* [What If You Don’t Know the Function/Purpose Yet?](https://www.nutrient.io/blog/naming-classes-why-it-matters-how-to-do-it-well/#what-if-you-dont-know-the-functionpurpose-yet)
* [It Is Easy to Name If You Have a Class That Does One Thing](https://www.nutrient.io/blog/naming-classes-why-it-matters-how-to-do-it-well/#it-is-easy-to-name-if-you-have-a-class-that-does-one-thing)
* [More Words != Better Naming](https://www.nutrient.io/blog/naming-classes-why-it-matters-how-to-do-it-well/#more-words--better-naming)
* [Talk to Your Team about Naming](https://www.nutrient.io/blog/naming-classes-why-it-matters-how-to-do-it-well/#talk-to-your-team-about-naming)
* [Use Documentation to Describe Small Details](https://www.nutrient.io/blog/naming-classes-why-it-matters-how-to-do-it-well/#use-documentation-to-describe-small-details)
* [What Is Wrong with Manager Though?](https://www.nutrient.io/blog/naming-classes-why-it-matters-how-to-do-it-well/#what-is-wrong-with-manager-though)
* [Conclusion](https://www.nutrient.io/blog/naming-classes-why-it-matters-how-to-do-it-well/#conclusion)
* [FAQ](https://www.nutrient.io/blog/naming-classes-why-it-matters-how-to-do-it-well/#faq)

[Try for free
Ready to get started?](https://www.nutrient.io/try/)

## Related SDK articles

[Explore more](https://www.nutrient.io/blog/categories/sdk/)

[![Six best PDF generator APIs in 2025: Nutrient vs. competitors compared](./Naming Classes — Why It Matters, and How to Do It Well_files/article-header.B00b1SBO_Z2fBE0x.png)](https://www.nutrient.io/blog/the-six-best-pdf-generator-apis/)

![Jonathan D. Rhyne](./Naming Classes — Why It Matters, and How to Do It Well_files/jonathan-d-rhyne.xChnw7U9_Y935U.jpg)

Jonathan D. Rhyne

## [Six best PDF generator APIs in 2025: Nutrient vs. competitors compared](https://www.nutrient.io/blog/the-six-best-pdf-generator-apis/)

[![From Zero to AI: Building custom chat interfaces with Nutrient on Android](./Naming Classes — Why It Matters, and How to Do It Well_files/article-header.C1STtf0S_Z1CgcuN.png)](https://www.nutrient.io/blog/from-zero-to-ai-building-custom-chat-interfaces-with-nutrient-on-android/)

![Akshay Sharma](./Naming Classes — Why It Matters, and How to Do It Well_files/akshay-sharma.D35S6FVg_Z1wis0M.jpg)

Akshay Sharma

## [From Zero to AI: Building custom chat interfaces with Nutrient on Android](https://www.nutrient.io/blog/from-zero-to-ai-building-custom-chat-interfaces-with-nutrient-on-android/)

[![Beginner’s guide to Docker commands](./Naming Classes — Why It Matters, and How to Do It Well_files/article-header.D0g-S3wV_1KowuI.png)](https://www.nutrient.io/blog/docker-import-export-vs-load-save/)

![William Meleyal](./Naming Classes — Why It Matters, and How to Do It Well_files/steffen.DzCEIadE_ZtdiTG.jpg)

William Meleyal

## [Beginner’s guide to Docker commands](https://www.nutrient.io/blog/docker-import-export-vs-load-save/)

popular

* [Java PDF Library](https://www.nutrient.io/sdk/java/)
* [PDF SDK Viewer](https://www.nutrient.io/sdk/solutions/viewing/)
* [React Native PDF SDK](https://www.nutrient.io/sdk/react-native/)
* [PDF SDK](https://www.nutrient.io/sdk/)
* [iOS PDF Viewer](https://www.nutrient.io/guides/ios/viewer/)
* [PDF Viewer SDK/Library](https://www.nutrient.io/guides/web/viewer/)
* [PDF Generation](https://www.nutrient.io/guides/document-engine/pdf-generation/)

SDK

* [Web](https://www.nutrient.io/sdk/web-overview/)
* [Mobile/VR](https://www.nutrient.io/sdk/mobile-overview/)
* [Server](https://www.nutrient.io/sdk/server-overview/)
* [Solutions](https://www.nutrient.io/sdk/solutions/)

Resources

* [Blog](https://www.nutrient.io/blog/sdk/)
* [Events](https://www.nutrient.io/events/)
* [Customer Stories](https://www.nutrient.io/blog/categories/customer-stories/)
* [Tutorials](https://www.nutrient.io/blog/categories/tutorials/)
* [Features List](https://www.nutrient.io/sdk/features-list/)
* [News](https://www.nutrient.io/blog/categories/news/)
* [Deployment Options](https://www.nutrient.io/sdk/deployment-options/)

Community

* [Try for free](https://www.nutrient.io/sdk/try/)
* [Documentation](https://www.nutrient.io/sdk/developers/)
* [Nutrient Portal](https://my.nutrient.io/)
* [Contact Support](https://support.nutrient.io/hc/en-us/requests/new)

Company

* [About](https://www.nutrient.io/company/about/)
* [Security](https://www.nutrient.io/security/)
* [Team](https://www.nutrient.io/company/team/)
* [Careers](https://www.nutrient.io/company/careers/)
* [Partners](https://www.nutrient.io/partners/)
* [Legal](https://www.nutrient.io/legal/privacy/)
* [News](https://www.nutrient.io/blog/categories/news/)

Connect

* [Contact](https://www.nutrient.io/company/contact/)
* [LinkedIn](https://www.linkedin.com/company/nutrientdocs)
* [YouTube](https://www.youtube.com/channel/UCQFsRxB1vTDJ5N1NaNsZNrw?sub_confirmation=1)
* [Discord](https://discord.gg/Z754Pfb8bD)
* [X](https://x.com/nutrientdocs)
* [Facebook](https://www.facebook.com/nutrientdocs/)

Copyright 2026 Nutrient. All rights reserved.

     ASK AI