inherit NPC;

void create()
{
        set_name("执法弟子", ({ "dizi" }));
        set("long","这是一个听命执法长老的丐帮弟子, 负责用刑。\n");
        
        set("gender", "男性");
        set("age", 33);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("str", 24);
        set("int", 18);
        set("con", 22);
        set("dex", 24);

        set("max_qi", 400);
        set("max_jing", 400);
        set("neili", 400);
        set("max_neili", 400);
        set("jiali", 20);
        set("combat_exp", 5000);

        set_skill("force", 35);
        set_skill("dodge", 35);
        set_skill("unarmed", 35);
        set_skill("parry", 35);


        setup();

        set("chat_chance", 5);
        set("chat_msg", ({
              "执法弟子叫道：“这般没用，亏你在丐帮中耽了这么久。”\n",
        }) );

}

