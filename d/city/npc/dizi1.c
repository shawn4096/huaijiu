// dizi1.c

inherit NPC;

void create()
{
        set_name("小乞丐",({ "xiao qigai", "qigai", "beggar" }) );
        set("gender", "男性" );
        set("age", 10);
        set("long", "这是一个刚入丐帮的小弟子，脸上还带着天真的笑容。\n");
	

        set("shen", -100);
        set("shen_type", -1);
        set("str", 15);
        set("dex", 18);
        set("con", 15);
        set("int", 17);
        set("combat_exp", 200);
        set_temp("apply/attack", 5);
        set_temp("apply/defense", 10);
        set("attitude", "peaceful");
        setup();
        
}

