// NPC: /d/huashan/npc/feng.c
// Date: Look 99/03/25

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("风清扬", ( {"feng qingyang","feng","qingyang"} ) );
        set("long", "一位神气抑郁，脸如金纸的老者。\n" );
        create_family("华山派", 12, "弟子");

        set("age", 91);
        set("gender", "男性");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("shen",150000);
        set("no_quest",1);

        set("con", 30);
        set("dex", 30);
        set("int", 40);
        set("str", 30);
	set("per", 24);
        set("max_jing", 6000);
        set("max_neili", 15000);
        set("max_qi", 7500);
        set("eff_jingli", 4000);
        set("neili", 15000);
        set("jiali", 100);
        set("combat_exp", 3000000);

        set_skill("sword",330);
        set_skill("force",200);
        set_skill("dodge",300);
        set_skill("parry",300);
        set_skill("dugu-jiujian",300);
        set_skill("huashan-shenfa",300);
        set_skill("huashan-jianfa",200);
        set_skill("zixia-gong",200);
        set_skill("zhengqi-jue",200);

        map_skill("force","zixia-gong");
        map_skill("sword","dugu-jiujian");
        map_skill("dodge","huashan-shenfa");
	map_skill("parry","dugu-jiujian");
	set_temp("apply/damage", 40);
        set_temp("apply/dodge", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/armor", 40);
	setup();
        carry_object(BINGQI_D("sword/sword"))->wield();
        carry_object(ARMOR_D("armor/cloth"))->wear();
}

void attempt_apprentice(object ob)
{
	if ( ob->query("family/family_name") != "华山派" && ob->query("is/huashan")==1 ) {
		message_vision(CYN "$N！你这个华山派的叛徒还回来干什么 ？？？\n"NOR, ob );
		command("slap "+ob->query("id"));
		return;
	}

        if (!ob->query("fengset")) {
		command("say 你我恐怕今生无缘，这位" + RANK_D->query_respect(ob) +
                        "还是请回吧。");
		command("wave " + ob->query("id"));
		return;
        }
        if (ob->query("shen") < ob->query("combat_exp")) {
		command("say 我华山派乃是堂堂名门正派，对弟子要求极严。");
		command("say 在德行方面，" + RANK_D->query_respect(ob) + "是否还做得不够？");
		return;
        }
        if ((int)ob->query_skill("zixia-gong",1)<180){
                command("say 这位" + RANK_D->query_respect(ob) +
                        "，你的紫霞神功等级过低，怕不能领悟我独孤九剑精髓。");
                return;
        }
        if ((int)ob->query_skill("huashan-shenfa",1)<180){
                command("say 这位" + RANK_D->query_respect(ob) +
                        "，你的华山身法等级过低，怕不能领悟我独孤九剑精髓。");
                return;
        }
        if ((int)ob->query_skill("huashan-jianfa",1)<180){
                command("say 这位" + RANK_D->query_respect(ob) +
                        "，你的华山剑法等级过低，怕不能领悟我独孤九剑精髓。");
                return;
        }

        command("say 好吧，我就收下你了,你可要为我们华山派争口气。");
        command("chat* 脸上浮现出一丝笑容，对着"+ob->query("name")+"笑道：我华山后继有人了。");
        command("chat* nomatch feng");
        command("recruit " + ob->query("id"));
        ob->set("is/huashan",1);
        ob->set("title",HIW"华山派风清扬传人"NOR);
}
