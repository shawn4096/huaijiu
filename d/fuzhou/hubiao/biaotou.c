inherit NPC;
void create()
{
        set_name("镖头", ({ "biaotou" }) );
        set("gender", "男性" );
        set("age", 25);
        set("combat_exp", 100000);
        set("attitude", "friendly");
        set("per",2);
        set("chat_chance", 2);
        set("chat_msg",({
        "镖头喝道：“闲杂人等闪开了。”\n",
        "镖头喝道：“快走快走，别偷懒！”\n",
    }) );

        set_temp("no_return",1);
        setup();
        carry_object("/clone/armor/bcloth")->wear();
        carry_object("/clone/weapon/blade")->wield();
}
