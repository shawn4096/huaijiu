// /u/dubei/miaojiang/npc/guaimang
//  怪蟒

inherit NPC;

void create()
{
        set_name("怪蟒", ({ "guai mang" }));
        set("race", "野兽");
        set("age", 200);
        set("long", "一条浑身漆黑，身体盘曲的怪蟒。 浑身发出阵阵强烈的腥臭味。\n");
        set("attitude", "aggressive");
        set("str", 70);
        set("con", 50);
        set("max_qi", 800);
        set("limbs", ({ "头部", "身体", "尾巴" }) );
        set("verbs", ({ "bite" }) );
        set("combat_exp", 350000);
        set_temp("apply/attack", 370);
        set_temp("apply/armor", 350);
        setup();
}
void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) &&
                random(ob->query_kar() + ob->query_per()) < 30) {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob); 
        }
}
void die()
{
// obiect ob;
        message_vision("$N抽搐了几下，身体缩在一起，死了。\n", this_object());
//        ob = new(__DIR__"msdan");
//        ob->move(environment(this_object()));
        destruct(this_object());
}
int hit_ob(object me, object victim, int damage)
{
	victim->apply_condition("snake_poison",
		victim->query_condition("snake_poison") + 35);
	return 0;
}        
