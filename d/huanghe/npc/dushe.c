// animal: snake.c
// Jay 3/18/96

inherit NPC;

void create()
{
        set_name("毒蛇", ({ "du she" }) );
        set("race", "野兽");
        set("age", 4);
        set("long", "一只有着三角形脑袋的蛇，尾巴沙沙做响。\n");
        set("attitude", "peaceful");
        set("no_get","你刚伸手触到蛇皮，就觉得一阵恶心，不由把手缩了回来。\n");

        set("str", 26);
        set("cor", 30);

        set("limbs", ({ "头部", "身体", "七寸", "尾巴" }) );
        set("verbs", ({ "bite" }) );

        set("combat_exp", 1000);

        set_temp("apply/attack", 15);
        set_temp("apply/damage", 6);
        set_temp("apply/armor", 2);

        setup();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) &&
                random(ob->query_kar()) < 30) {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob); 
        }
}

void die()
{
        object ob;
        message_vision("$N啪的一声断成两截！$N死了。\n", this_object());
        ob = new("/d/xingxiu/obj/shedan");
        ob->move(environment(this_object()));
        destruct(this_object());
}

int hit_ob(object me, object victim, int damage)
{
        victim->apply_condition("snake_poison",
                victim->query_condition("snake_poison") + 6);
        return 0;
}
