#include <ansi.h>
inherit NPC;
void create()
{
        
	set_name("曲洋", ({ "qu yang", "qu",}));
        set("long", 
"此人乃日月神教十大长老之一，武功深不可测。
而他更痴迷于琴曲之道，琴艺可以称得上是当世第一人.\n");
        set("title",HIY"日月神教  "HIG"长老"NOR);
        set("gender", "男性");
        set("age", 60);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);
        set("max_qi", 700);
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 600);
        set("jiali", 50);
        set("combat_exp", 100000);
        set("shen", -1000);
       
 	set_skill("tianmo-zhang",100);
        set_skill("strike", 100);
        set_skill("parry",100);
        set_skill("dodge",100);
        set_skill("ding-dodge",100);        
        set_skill("force",100);
        set_skill("huntian-qigong",100);
        

        map_skill("dodge", "ding-dodge");
        map_skill("force", "huntian-qigong");
        map_skill("strike", "tianmo-zhang");
	map_skill("parry", "tianmo-zhang");
	
        setup();
	carry_object("/d/hmy/npc/obj/bi")->wield();
	carry_object("/d/hmy/npc/obj/cloth")->wear();        

}

void init()
{
        object ob;
        
        ::init();
        
        if( interactive(ob = this_player()) )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        object me = this_object();
        
        if (!ob || !present(ob, environment())) return;
// 判断 player        
        if (ob->query("hostage/toone")
        &&  me->query("target") == ob->query("id"))
        {
                command("look " + ob->query("id"));
                command("say " + RANK_D->query_rude(ob) + "，你休想把人质从这里带走！");
                ob->start_busy(random(2));
                remove_call_out("do_kill");
                call_out("do_kill", 0, ob);
        }
}

void do_kill(object ob)
{
	remove_call_out("kill_ob");
	call_out("kill_ob",0,ob);
}

void die()
{
        object ob = this_object();
        object me = this_player();
        
       	ob->revive(1);
       	command("sneer");
	command("escape");
       	me->set_temp("hostage/killed_qu",1);
	destruct(ob);
	return;
	        
        ::die();
}
