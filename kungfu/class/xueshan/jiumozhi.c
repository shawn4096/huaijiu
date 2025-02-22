// jiumozhi.c 鸠摩智
// by iceland

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("鸠摩智", ({ "jiumo zhi", "jiumozhi","zhi" }));
        set("long",@LONG
他身材匀称，脸上神采飞扬，隐隐似有宝光流动，便如是明珠宝玉，自然生辉，
只消向他看得几眼，便生钦仰亲近之意。
LONG
        );
        set("title", HIY "大轮寺掌门" NOR);
        set("gender", "男性");
        set("class", "huanxi");
        set("age", 55);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 35);
        set("int", 40);
        set("con", 30);
        set("dex", 30);
        set("per", 25);
        set("max_qi", 6500);
        set("eff_jingli", 3500);
        set("max_jing", 6000);
        set("neili", 14000);
        set("max_neili", 14000);
        set("jiali", 80);
        set("combat_exp", 2900000);
        set("score", 290000);
        set("unique", 1);

        set_skill("huanxi-chan", 200);
        set_skill("literate", 150);
        set_skill("force", 200);
        set_skill("longxiang-boruo", 200);
        set_skill("dodge", 290);
        set_skill("yuxue-dunxing", 290);
        set_skill("strike", 290);
        set_skill("huoyan-dao", 300);
        set_skill("parry", 290 );
        set_skill("staff",290);
        set_skill("wushang-dali",290);

        map_skill("force", "longxiang-boruo");
        map_skill("dodge", "yuxue-dunxing");
        map_skill("strike", "huoyan-dao");
        map_skill("staff","wushang-dali");
        map_skill("parry", "huoyan-dao");

        prepare_skill("strike","huoyan-dao");

        create_family("大轮寺", 10, "弟子");
        set("class", "huanxi");
        set("chat_chance", 2);     
        set("chat_msg", ({
"鸠摩智低头沉思，说到：嵩山少林寺，大理天龙寺，哼！我大轮寺那点比不上？！\n",
"鸠摩智将双掌举到眼前瞧了瞧，冷笑了一声：天下能有几人是我的敌手？！\n",
}) );

        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: exert_function, "shield jiumo zhi" :),
                (: perform_action, "strike.fen" :), }));

	set_temp("apply/armor", 60);
        set_temp("apply/damage", 50);
        set_temp("apply/attack", 60);
        set_temp("apply/dodge", 50);
        setup();
        carry_object("/d/xueshan/npc/obj/longxiang-jiasha")->wear();

//      add_money("gold",5);
}

void attempt_apprentice(object ob)
{
        if( (string)ob->query("gender") == "无性" ) {
                command("say 施主身体残缺，虽说佛祖普渡众生，可是...\n");
                return;
        }
        if ((string)ob->query("family/family_name") != "大轮寺") {
                command("say"+ RANK_D->query_respect(ob) +
                        "不是本寺弟子，在这里捣什么乱？！");
                return;
        }
        if ((int)ob->query_skill("longxiang-boruo", 1) < 160) {
                command("say 我大轮寺各种武功均和内功相辅相成。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多钻研钻研本门的内功吧。");
                return;
        }
        if (((int)ob->query_con() < 32) || ((int)ob->query_str() < 32))
{
                command("hmm");
                command(
"say 这位" + RANK_D->query_respect(ob) +"体质似乎不适合学习我火焰刀神功，\n
还是尽早想想别的出路吧。");
                return;
        }
       command("say 看你根骨精奇，确实是练武的好材料，好吧，就让我来好好调教调教你吧。");
       command("recruit " + ob->query("id"));
       ob->set("title", HIY "大轮寺掌门座下弟子" NOR);
}

