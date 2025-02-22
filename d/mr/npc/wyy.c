//wang.c

inherit NPC;

void create()
{
        set_name("王语嫣", ({ "wang yuyan", "wang" }));
        set("long", "她生得极为美貌,一双眼睛顾盼生辉.\n");
        set("nickname", "天下无不知");
           set("title","曼佗罗山庄庄主之女");
        set("gender", "女性");
        set("unique", 1);
        set("age", 20);
        set("attitude","friendly");
        set("str", 30);
        set("dex", 30);
        set("con", 30);
        set("int", 30);
        set("per", 30);
        set("max_qi", 5000);
        set("max_jing", 1000);
        set("neili", 3000);
        set("max_neili", 3000);

        setup();
        carry_object(__DIR__"obj/skirt1")->wear();        carry_object(__DIR__"obj/shoe")->wear();        carry_object(__DIR__"obj/green_silk")->wear();
}

void init()
{
        add_action("lingwu","ask");
}

int lingwu(string arg)
{
        object me=this_player();
        object where = environment(me);
        string special;
        int bl,sl;
        string name;
        if (!arg) return 0;
        if (!sscanf(arg, "%s about %s", name, arg)) return 0;
        if (!id(name)) return 0;

        if (!me->query("luohan_winner")) return notify_fail("你级别不够，不能在此领悟。\n");
        write( "你向王语嫣请教关于「" + to_chinese(arg) + "」的疑问。\n");
        if (me->is_busy() || me->is_fighting()) {
                command("say 你正忙着呢。");
                return 1;
        }
        if(where->query("lingwu") != 1 )
                return notify_fail("你只能在娘缳玉洞向王姑娘领悟武功。\n");
        if (!(special=me->query_skill_mapped(arg))) {
                if (arg == to_chinese(arg))
                        command("say 「" + arg + "」是什么武功？怎么我没听说过？");
                else
                        command("say 我只能从你的特殊技能中给你指点。");
		me->add_busy(1);
                return 1;
        }
        if (!me->query_skill(arg,1)) {
                command("say 你不会这种技能。");
		me->add_busy(1);
                return 1;
        }
    if (arg == "force" && (int)me->query_skill("force",1)<200) {
                command("shake");
                command("say 你目前修为尚浅，不宜自己领悟基本内功。");
		me->add_busy(1);
                return 1;
        }
        if((int)me->query("potential", 1) < 1 ) {
		me->add_busy(1);
                write("你从实战中得到的潜能已经用完了。\n");
		return 1;
	}
        bl=me->query_skill(arg,1);
        if (bl > me->query("jing") || me->query("jing")*100/me->query("max_jing") < 50) {
                me->receive_damage("jing",bl/2);
                command("say " + RANK_D->query_respect(me) + "先休息一下吧。");
		me->add_busy(1);
                return 1;
        }
        sl=me->query_skill(special,1);
        if (bl > sl) {
                command("say " + RANK_D->query_respect(me) + "的"+to_chinese(special)+"造诣不够，我不能指点你更深一层的"+to_chinese(arg)+"。");
		me->add_busy(1);
                return 1;
        }
        write("你听了" + name() + "的指点，对"+to_chinese(arg)+"的体会又深了一层。\n");
        me->receive_damage("jing",bl/5*3);
if(random(5)>2) me->add("potential",-1);
me->improve_skill(arg,(int)(me->query_skill("literate",1))/3+5);
if(me->query("age")<30)me->improve_skill(arg,30-me->query("age"));
if(me->query("age")>60)me->improve_skill(arg,me->query("age")-60);
        return 1;
}

void kill_ob(object ob)
{
        ob->remove_killer(this_object());
        remove_killer(ob);
        command("peace " + ob->query("id"));
}

