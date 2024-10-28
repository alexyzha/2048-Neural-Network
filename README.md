# N-Tuple Neural Network Plays 2048

The largest tile you can realistically reach in the game [`2048`](https://2048.io) is `131,072`. However, unless you're an ultra-sweat or something, you probably only care about reaching `2048` and maybe `4096` or even `8192`. The average human being with a brain is able to do this fairly easily, but what about a computer?

There are a total of `12^16` possible states for the `2048` board for values of tiles ranging from 2 to 2048. While this is nowhere near the amount of possible states for games like Chess or Go, it does mean that an AI agent of some kind is needed to "solve" `2048`.

Throughout many studies over the years, it has been proven that one of the best structures for an autonomous `2048` player is an N-tuple network.





# References

1. K. Matsuzaki, "Systematic selection of N-tuple networks with consideration of interinfluence for game 2048," 2016 Conference on Technologies and Applications of Artificial Intelligence (TAAI), Hsinchu, Taiwan, 2016, pp. 186-193, [doi](10.1109/TAAI.2016.7880154)

2. M. Szubert and W. Jaśkowski, "Temporal difference learning of N-tuple networks for the game 2048," 2014 IEEE Conference on Computational Intelligence and Games, Dortmund, Germany, 2014, pp. 1-8, [doi](10.1109/CIG.2014.6932907)

3. “The Mathematics of 2048: Counting States with Combinatorics,” jdlm.info, Sep. 17, 2017. [web](https://jdlm.info/articles/2017/09/17/counting-states-combinatorics-2048.html)