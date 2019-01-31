// mawude.c �����

#include <ansi.h>
#include <localtime.h>
inherit NPC;

int ask_me1();
int ask_me2();
private void set_enter_date(object ob,int date);
private int query_date(int date);

void create()
{
        set_name("�����", ({ "ma wude", "ma", "wude" }) );
	set("gender", "����");         
        set("title", "�����ն�����ʦ");
        set("age", 65);
	set("long","������Ǵ���̣������ÿͣ������ϳ�֮�硣\n");
        set("combat_exp", 200000);
        set("shen_type", 1);
	set("attitude", "peaceful");
        set("unique", 1);

        set("str", 28);
        set("con", 26);
	set("int", 20);
	set("dex", 24);
        set("per", 13);

        set("max_qi", 800);
        set("max_jing", 500);
        set("neili", 800);
        set("eff_jingli", 500);
        set("max_neili", 800);
       
        set_skill("force", 80);  
        set_skill("yijin-jing", 80);
        set_skill("sword", 80);
        set_skill("dodge", 80);
        set_skill("strike", 80);
        set_skill("cuff", 80);
        set_skill("weituo-zhang", 80);
        set_skill("parry", 80);
        set_skill("luohan-quan",80);
        set_skill("shaolin-shenfa", 80);
        map_skill("parry", "luohan-quan");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "luohan-quan");
        map_skill("force","yijin-jing");
        map_skill("strike", "weituo-zhang");
        prepare_skill("strike", "weituo-zhang");
        prepare_skill("cuff", "luohan-quan");

        set("inquiry", ([
                "����" : (: ask_me1 :),
                "����" : (: ask_me2 :),

        ]));
        set("chat_chance", 5);
        set("chat_msg", ({
        "�����������ݣ���:ֻʣ��һ��,������Ȥ����\n",
        "�����������Թ��:�����ң�����ʲô�ƾӺ������ͷ����!˭֪�⴬��...\n",
        }) );
	setup();
        carry_object("/clone/misc/cloth")->wear();
}

int ask_me1()
{
        object ob = this_player();

        command("say ����͢��ӹ���������С���������С�϶��������ƾӺ��⡣\n"
                "���ϣ������˻��Ĵ����ں��ϱ�ǿ�����ӡ�Ǯ�Ʊ�������֮�ֻ����ҳ����ܰ��ݡ�\n"
                "�����ѻ�֪ǿ�����ڣ���֪" + RANK_D->query_respect(ob) + "�Ƿ���������...\n");

        ob->set_temp("marks/�´�������1",1);
     
        return 1;
}

int ask_me2()
{
        object ob = this_player();
        int sysdate;

        if (ob->query("dmd_enter_time")) 
	       set_enter_date(ob,ob->query("dmd_enter_time"));
  
        if(!ob->query_temp("marks/�´�������1")) {
               command("say " + RANK_D->query_respect(ob) + "�γ����ԣ�\n");
               return 1;
         }
        
        if( ob->query("combat_exp") < 2500000 ) {
	       command("disapp "+(string)ob->query("id"));
	       command("say ��������ǿ�˳�û��������֣��㻹�ǿ������������ɣ�\n");
               ob->delete_temp("marks/�´�������1",1);
	       return 1;
	  }

	sysdate=query_date(time());
        if( ob->query("dmd_enter_date") && sysdate <= ob->query("dmd_enter_date") && !wizardp(ob)) {
               command("say ��������ʮ��ƣ�����������������ɡ�\n");
               tell_object(ob,HIG"���ϴν����´�������������ʱ����"+CHINESE_D->chinese_date(ob->query("dmd_enter_time"),1)+"��\n"NOR);
               return 1;
        }

	  command("touch "+(string)ob->query("id"));
	  command("say ���ڷ�ɽ��ͷ�ѹͺ�һ�ҿ촬��" + RANK_D->query_respect(ob) + "ֱ�����ϴ��ҵ����ż��ɣ�\n");

        ob->delete_temp("marks/�´�������1");
        ob->set_temp("marks/�´�������2",1);

        return 1;
      
}

private void set_enter_date(object ob,int date)
{
		mixed *local;
		int y, m, d;
		string dmd_enter_date;
		
		local = localtime(date);
		d = local[LT_MDAY];
		m = local[LT_MON]+1;
		y = local[LT_YEAR];
		
		if (m<10) {
                  if (d<10)  
                          dmd_enter_date=y+"0"+m+"0"+d;
		      else
			        dmd_enter_date=y+"0"+m+d;
                  }
            else {
                  if (d<10)  
                          dmd_enter_date=""+y+m+"0"+d;
		      else
			        dmd_enter_date=""+y+m+d;
                  }

		ob->set("dmd_enter_date",dmd_enter_date);

}
private int query_date(int date)
{
		mixed *local;
		int y, m, d;
		string query_date;
		
		local = localtime(date);
		d = local[LT_MDAY];
		m = local[LT_MON]+1;
		y = local[LT_YEAR];
		
		if (m<10) {
                  if (d<10)  
                          query_date=y+"0"+m+"0"+d;
		      else
		              query_date=y+"0"+m+d;
                  }
            else {
                  if (d<10)  
                          query_date=""+y+m+"0"+d;
		      else
			        query_date=""+y+m+d;
                  }

		return (int)query_date;

}