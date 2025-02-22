// fusigui.c
// Modify By River 98/12
#include <ansi.h>
inherit NPC;

string ask_join();

void create()
{
        set_name("傅思归", ({ "fu sigui", "fu", "sigui" }));
        set("title", "大理国镇南王府家将");
        set("gender", "男性");
        set("age", 33);
        set("str", 25);
        set("unique", 1);
        set("dex", 25);
        set("long", "这人身穿军服，三十来岁，虎背熊腰，手持一根熟铜棍。\n");
        set("combat_exp", 400000);
        set("shen_type", 1);
        set("attitude", "friendly");

        set_skill("strike", 60);
        set_skill("club",90);
        set_skill("qiantian-yiyang", 100);
        set_skill("tianlong-xiang", 100);
        set_skill("qingyan-zhang", 80);
        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("weituo-gun", 100);
        set_temp("apply/defense", 70);
        set_temp("apply/armor", 70);
        map_skill("force", "qiantian-yiyang");
        map_skill("strike", "qingyan-zhang");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "qingyan-zhang");
        map_skill("club", "weituo-gun");
        prepare_skill("strike","qingyan-zhang");

        set("max_qi", 900);
        set("neili", 900); 
        set("max_neili", 900);
        set("jiali", 20);
        set("inquiry",([
           "入官府" : (: ask_join :),
           "join" : (: ask_join :),
        ]));

        set("chat_chance", 3);
        set("chat_msg", ({
           "傅思归说道: 镇南王广招天下豪杰，诚心相待。作奸犯科，行为不轨的小人我们可不想招纳。 \n",
        }));

        setup();
        carry_object(__DIR__"obj/tonggun")->wield();
        carry_object("/d/dali/npc/obj/zipao")->wear();
}

string ask_join()
{
        object ob = this_player();

     if (ob->query("combat_exp")<3000)
                     return ("你的武功太差，什么也做不了的。\n");

        if (ob->query_temp("dali_join"))
                return RANK_D->query_respect(ob) + "已经是本王府随从了，何故还要开这种玩笑？";

	if (ob->name() != ob->name(1)) {
		command("hmm " + ob->query("id"));
		return RANK_D->query_respect(ob) + "不肯以真面目示人，还是另谋高就吧！";
	}

	ob->set_temp("dali_join",1);
//	ob->set_temp("apply/short", ({ HIY"大理国镇南王府随从 "NOR + ob->short(1) }));
// + "(" + capitalize(ob->query("id")) + ")" }));
       command("look "+ob->query("id"));
	return "好，不错，这位"+RANK_D->query_respect(ob)+"可以为本王府工作了。";
}
