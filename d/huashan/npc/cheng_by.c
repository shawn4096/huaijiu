// NPC: /d/huashan/npc/cheng_by.c
// Date: Look 99/03/25

inherit NPC;

void create()
{
        set_name("成不忧",({"cheng buyou", "cheng", "buyou" }));
        set("title","华山派第十三代剑宗大弟子");
        set("nickname","矮剑客");
        set("long", "乍看上去只不过是一个平凡的矮子，但目光凶恶逼人。\n");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("no_quest",1);
        
        set("max_qi",2500);
        set("qi", 2500);
        set("max_jing", 1400);
        set("jing",1400);
        set("eff_jingli", 1700);
        set("jingli", 1700);
        set("max_neili", 3500);
        set("neili", 3500);
        set("jiali", 50);
        set("combat_exp", 1000000);
        set("score", 30000);
        set("chat_chance_combat",40);
        set("chat_msg_combat", ({
        (: perform_action, "strike.wuji" :),
        }));
        set_skill("strike", 140);
        set_skill("hunyuan-zhang", 140);
        set_skill("sword",  140);
        set_skill("dodge",  140);
        set_skill("force",  140);
        set_skill("parry",  140);
        set_skill("zixia-gong", 100);
        set_skill("huashan-jianfa",  160);
        set_skill("huashan-shenfa",  160);

        map_skill("dodge", "huashan-shenfa");
        map_skill("force","zixia-gong");
        map_skill("sword","huashan-jianfa");
        map_skill("parry","huashan-jianfa");
        map_skill("strike","hunyuan-zhang");
        prepare_skill("strike","hunyuan-zhang");
        create_family("华山派",13,"弟子");

        setup();
	 carry_object(BINGQI_D("sword/sword"))->wield();
	 carry_object(ARMOR_D("armor/cloth"))->wear();
}

void init()
{
        object me, ob;
        ::init();

        ob = this_player();
        me = this_object();

        if (interactive(ob) && !environment(ob)->query("no_fight"))
        {
                       command("say 敢进入我剑宗禁地,只有死！！！\n");
                       me->set_leader(ob);
                       remove_call_out("kill_ob");
                       call_out("kill_ob", 1, ob); 
        }
}
