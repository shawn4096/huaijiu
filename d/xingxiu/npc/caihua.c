inherit NPC;

void create()
{
        set_name("采花子", ({ "caihua zi", "caihua", "zi" }) );
        set("gender", "男性" );
        set("nickname", "赛昆仑");
        set("age", 28);
        set("long", 
             "采花子是星宿派的一淫魔。生性淫邪，武功很差。"
             "经常奸淫星宿海周围的妇女, 别号赛昆仑。\n");
        set("env/wimpy", 40);
        set("str", 25);
        set("dex", 30);
        set("con", 17);
        set("int", 15);
        set("per", 20);
        set("shen", -300);
        set_skill("unarmed", 60);
        set_skill("force", 50);
        set_skill("dodge", 50);
        set_skill("zhaixingshu", 60);
        map_skill("dodge","zhaixingshu");
        set("combat_exp", 15000);

        set("max_qi", 500);
        set("max_jing", 500);

        create_family("星宿派", 2, "弟子");

        set("attitude", "peaceful");
        set("inquiry", ([
            "name" : "大爷我赛昆仑便是。",
            "采花" : "嘿嘿，娘儿们闲着，岂不是浪费了？",
       ]) );

        setup();
        carry_object(ARMOR_D("pink_cloth"))->wear();
//        add_money("silver", 10);
}
void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object me)
{
        mapping myfam;

	if (!me) return;
        myfam = (mapping)me->query("family");
        if (myfam && myfam["family_name"] == "星宿派"
               && (me->query("gender")=="男性"))
        command("say 我昨天从山下又捉了个小妞来。折腾了一夜，大爷我爽够了"
                +"，你进去试试吧。");
        me->set_temp("marks/花",0);
}

void attempt_apprentice(object ob)
{
    command("hehe");
    command("say 我这采花神功是天生的，你那能懂！");
        return;
}

int accept_object(object me, object obj)
{
        mapping myfam;
        myfam = (mapping)me->query("family");

        if (!myfam || myfam["family_name"] != "星宿派") {
          command("say 少跟我套近乎。");
	  return 0;
	} else {
		if (userp(obj)) {
			command("smile " + me->query("id"));
			me->set_temp("last_damage_from", "巨毒发作而");
			me->die();
			return 0;
		}
            if (me->query("gender")=="女性") {
                command("kiss " + me->query("id"));
                command("say 想不到师姐也有这个爱好。");
            }
            else {
                command("bow " + me->query("id"));
                command("say 多谢师兄。");
            }
            command("say 对不起，那小妞昨天晚上被不知道哪个混蛋救走了，不过"
                        + "你可以进洞睡一觉。");
            me->set_temp("marks/花", 1);
        }
	if (obj->query("money_id")) return 1;
	destruct(obj);
        return notify_fail("");
}
