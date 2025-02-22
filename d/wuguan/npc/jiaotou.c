// jiaotou.c 武馆教头
inherit NPC;

void create()
{              
        set_name("武馆教头", ({ "wuguan jiaotou", "jiaotou"}));
        set("long", "这是武馆聘请的教头，有什么不懂，你可以问他。\n"+
                     "例如：ask jiaotou about force。\n");
        set("gender", "男性");
        set("age", 41);
        set("unique", 1);
         
        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("strike", 80);
        set_skill("cuff", 80);
        set_skill("hand", 80);
        set_skill("sword", 80);
        set("jiali", 50);
        set("apply/attack", 30);
        set("apply/defense", 30);
        set("apply/damage", 35);
        set("combat_exp", 200000);
        set("shen_type", 1);
          
        set("chat_chance", 3);
        set("chat_msg", ({
                 "武馆教头喊道：大家好好练啊，有什么不懂可以问我。\n",
                 "武馆教头东看西瞧：你们可不要偷懒哦，大家加油啊。\n",
                 (: random_move :)
        }) );

        setup();
        carry_object(ARMOR_D("beixin"))->wear();      
}

void init()
{
        object ob,me;
        me=this_object();
        ::init();
        if (interactive(ob = this_player())
         && (int)ob->query_condition("killer")){ 
           command("say 你竟敢在武馆杀人! \n");
           me->set_leader(ob);
           remove_call_out("kill_ob");
           call_out("kill_ob", 1, ob);
        }
        add_action("do_lingwu", ({ "ask", "learn" }));
}

int is_apprentice_of( )
{
	return 1;
}

int do_lingwu(string arg)
{
        object me=this_player(), ob = this_object();               
        string name;
        if (!arg) return 0;
        if (!sscanf(arg, "%s about %s", name, arg))
	if (!sscanf(arg, "%s %s", name, arg)) return 0;
        if (!id(name)) return 0;

        message_vision("$N向$n请教关于「" + to_chinese(arg) + "」的疑问。\n", me, ob);

        if (me->is_busy() || me->is_fighting()) {
           command("say 你正忙着呢。");
           return 1;
        } 
        if( me->query("jing") < 10)
            return notify_fail("你太累了，还是休息一会吧。\n"); 
        if((int)me->query("potential", 1) < 1 ) 
           return notify_fail("你潜能不够，已经用完了。\n");
        if ((int)me->query_skill(arg) > 30) {
           command("say 你已经不能从我这里再学到什么了。");
           return 1;
        }                

        if ( arg =="whip" || arg== "blade" || arg== "dodge" || arg=="finger" || arg=="force" || arg=="sword" || arg=="hand"
          || arg =="cuff" || arg== "strike" || arg=="axe" || arg=="parry" || arg=="stick" || arg=="staff" || arg=="hammer" 
          || arg== "club" || arg== "leg"){                               
          write("你听了" + name() + "的指点，对"+to_chinese(arg)+"的体会又深了一层。\n");
          me->receive_damage("jing", 5+random(5));
          me->add("potential", -1);
          me->improve_skill(arg, random(me->query_int())/2);
          return 1;
        }
        command("dunno "+me->query("id"));
        return 1;        
}
