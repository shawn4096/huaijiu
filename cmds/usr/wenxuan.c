// wenxuan.c
/*

   by snowman@SJ 23/04/1999

   Copyright 1997-1999 ShuJian MUD Wizard Group.
   All rights reserved.

Modify by bbb 2000/12/16 ,wenxuan->homepage mysql
*/

#include <ansi.h>
#include <localtime.h>

#define Data_Base_Online

// 省缺的文选目录。
#define WENXUAN_DIR     "/data/wenxuan/"
#define TEXT_LINE       "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"

inherit F_CLEAN_UP;
int help(object me);
int list(object me, int y, int m);
int read_note(object me, int number, int m, int y);

/* 主程序。*/
int main(object me, string arg)
{
        mapping *notes;
        object board;
        string *file, str, msg;
        int i, j, num, number,m,y;
        
// data_base_only.
#ifdef Data_Base_Online
        int mysql,rows;
        mixed userid;
#endif

        // 标题。
        tell_object(me,HIW"\n《"NOR + MUD_NAME + HIW"文选大全"NOR + HIW"》"NOR"，");

        // 获取目前的年份(y)和月份(m)。
        m = localtime(time())[LT_MON] + 1;
        y = localtime(time())[LT_YEAR];

        file = get_dir(WENXUAN_DIR);
        i = sizeof(file);

        // 不加任何参数，就输出列表。
        if (!arg) {
                if (!i) return notify_fail("现在暂时还没有文选。\n");
                else list(me, y, m);
        }

        // 输出帮助。
        else if (arg == "?") return help(me);

        // 列出所有收录有文选的年份。
        else if(arg == "all"){
                str = "目前有 ";
                while(i--) str += "[" + file[i] + "年] ";
                tell_object(me, str + "的文选。\n");
        }

        // 参数中有年份和月份。
        else if(sscanf(arg, "%d %d %d", number, m, j)==3){
                if(m < 1 || m > 12)
                        return notify_fail("有“" + chinese_number(m) + "月”这个月份吗？\n");
                if(j < 1970 || j > y )
                        return notify_fail("还没有 [" + j + "] 这年的文选呢。\n");
                // 列表。
                if(number == 0)
                        list(me, j, m);
                // 阅读。
                else read_note(me, number, m, j);
        }

        // 参数中有月份。
        else if(sscanf(arg, "%d %d", number, m)==2){
                if(m < 1 || m > 12)
                        return notify_fail("有“" + chinese_number(m) + "月”这个月份吗？\n");
                // 列表。
                if(number == 0)
                        list(me, y, m);
                // 阅读。
                else read_note(me, number, m, y);
        }

        // 参数中为编号，阅读文选。
        else if(sscanf(arg, "%d", number) == 1)
                read_note(me, number, m, y);

        // 添加文选。
        else if(sscanf(arg, "add %d", num) == 1){
                // Player不可对文选进行操作。
                if(!wizardp(me))
                        return help(me);

                if(num < 1)
                        return notify_fail("留言编号不正确。\n");

                if(!objectp(board = present("board", environment(me))))
                        return notify_fail("这里没有留言板。\n");

                if( !notes = board->query("notes") || !arrayp(notes) )
                        return notify_fail("留言板出错，请检查。\n");

                i = sizeof(notes);
                if( num > i) return notify_fail("此板上共有 "+sizeof(notes)+" 张留言，请输入正确的编号。\n");

                num--;
                number = 1;

                str = WENXUAN_DIR + y + "/" + m + "/";

                // 新月份或新年份。
                if(!get_dir(str)) assure_file(str + number + ".w");

                else  number = sizeof(get_dir(str + "*.w")) + 1;

                // 创建标题。
                msg = sprintf("%-=36s %18s (%s)\n",notes[num]["title"], notes[num]["author"],ctime(notes[num]["time"])[0..15]);

                // 写成 .w 文选文件。
                write_file(str + number + ".w", msg + TEXT_LINE + notes[num]["msg"] , 1);
                
                // 加入到数据库
                // send to web site.

//hxsd修改
/*
#ifdef Data_Base_Online
                mysql = db_connect("localhost","bbs","root");
                if (intp(mysql)) {
                        userid = explode(notes[num]["author"],"(");
                        userid = replace_string(userid[1],")","");
                        rows = db_exec(mysql, "insert into Posts set
                                B_Board='best',
                                B_Posted = \""+notes[num]["time"]+"\",
                                B_Last_Post = \""+notes[num]["time"]+"\",
                                B_Username= \""+userid+"\",
                                B_IP= \"202.97.175.44\",
                                B_Subject= '"+notes[num]["title"]+"',
                                B_Body= '"+notes[num]["msg"]+"',
                                B_Icon=\"book.gif\"");
                        if (intp(rows)) {
                                rows = db_exec(mysql, "update Users set
                                        U_Total = U_Total +50
                                        where U_Username = \""+userid+"\"");
                                if (intp(rows)) {
                                        write("添加到主页精华区 ......... 发送完毕，作者已经加社区积分 50 奖励。\n");
                                }
                                else {
                                        write("添加到主页精华区 ......... 发送完毕，50 分奖励未能成功增加。\n");
                                }
                        }
                        else {
                                write("添加到主页精华区 ......... 发送失败，详细信息为：\n"+rows+"\n请通知 bbb 解决此问题。\n");
                        }
                }
                else {
                        write("只可以在辽宁站发送，假如你是在辽宁站，目前数据库无法连接，请通知 bbb。\n");
                }
                db_close(mysql);
#endif
*/
                return notify_fail("你将第 " + (num + 1) + " 号留言放入文选 " + y + " 年 " + m + " 月第 " + number + " 号....Ok。\n");
        }

        // 删除文选。
        else if(sscanf(arg, "del %s", arg) == 1){
                // Player不可对文选进行操作。
                if(!wizardp(me)) return help(me);

                if( sscanf(arg, "%d %d %d", num, m, y) != 3 )
                        if( sscanf(arg, "%d %d", num, m) != 2 )
                                if( sscanf(arg, "%d", num) != 1 )
                                        if( sscanf(arg, "%s", msg) != 1 )
                                                return notify_fail("指令格式：dlwx <编号|all> [月份] [年份]\n");

                str = WENXUAN_DIR + y + "/" + m + "/";

                // 此月没有文选。
                if(!get_dir(str))
                        return notify_fail(" " + y + " 年 " + m + " 月没有文选。\n");

                // 删除此月所有文选。
                else if(msg && msg == "all"){
                        // 删除此目录中所有文件。
                        rm(str);
                        // 删除此目录。
                        rmdir(str);
                        return notify_fail("你将 " + y + " 年 " + m + " 月所有文选都删除了....Ok。\n");
                }

                if(num < 1)
                        return notify_fail("文选编号不正确。\n");

                if(file_size(str + num + ".w") <= 0)
                        return notify_fail(" " + y + " 年 " + m + " 月没有你所指的这篇文选。\n");

                i = sizeof(get_dir(str));

                // 删除此文选文件。
                rm(str+num+".w");

                // 重新排列文选文件。
                if(num < i)
                        for(j = num + 1; j <= i; j++)
                                if(file_size(str + j + ".w") > 0){
                                        cp(str + j + ".w", str + (j - 1) + ".w");
                                        rm(str + j + ".w");
                                }

                return notify_fail("你将 "+y+" 年 "+m+" 月第 " + num + " 号文选删除了....Ok。\n");
        }

        else help(me);

        return 1;
}

/* 列出文选。*/
// m = 月份， y = 年份
int list(object me, int y, int m)
{
        string *note;
        string str;
        int i, j;

        tell_object(me, y + " 年 " + m + " 月");

        // 获取文件数目。
        note = get_dir(WENXUAN_DIR + y + "/" + m + "/*.w");
        i = sizeof(note);

        if (!i){
                write("还没有任何文选。\n");
                return 0;
        }

        write("共有"+chinese_number(i)+"张文选。\n");
        str = TEXT_LINE;

        // 开始列表。
        for(j = 0; j < i; j++)
                str += " [" + (j + 1) + "] "+read_file(WENXUAN_DIR + y + "/" + m + "/" + (j + 1) + ".w", 1, 1);

        str += TEXT_LINE;
        str += HIW"请用 help wenxuan 或 wenxuan ? 查看使用方法。\n"NOR;
        // 输出。
        me->start_more(str);
        return 1;

}

/* 阅读文选。*/

// number = 篇数，m = 月份， y = 年份
int read_note(object me, int number, int m, int y)
{
        string *note;
        int i;

        tell_object(me, y + " 年 " + m + " 月");
        note = get_dir(WENXUAN_DIR + y + "/" + m + "/*.w");
        i = sizeof(note);

        if (!i){
                write("还没有任何文选。\n");
                return 0;
        }

        if( number < 1 || number > i ){
                write("目前还没有你所要读的这篇文选。\n");
                return 0;
        }

        write("的第" + chinese_number(number) + "张文选。\n\n");

        // 输出。
        me->start_more( " [" + number + "] " + read_file(WENXUAN_DIR + y + "/" + m + "/" + number + ".w"));
        return 1;

}


int help(object me)
{
        write(@HELP
指令格式：

wenxuan all                  : 列出有文选的年份。
wenxuan                      : 列出本月文选。
wenxuan <编号>               : 阅读本月此编号的文章。
wenxuan 0 <月份>             : 列出本年此月份文选。
wenxuan <编号> <月份>        : 阅读此月份此编号的文章。
wenxuan 0 <月份><年份>       : 列出此年份此月份文选。
wenxuan <编号> <月份> <年份> : 阅读此年份此月份此编号的文章。

巫师专用：

wenxuan add <留言编号> 文选一旦 add, 自动进主页精华区
wenxuan del <编号|all> [月份] [年份]

wenxuan del all                    : 删出本月所有文选。
wenxuan del <编号>                 : 删出本月此编号的文选。
wenxuan del <编号> [月份]          : 删出此月份此编号的文选。
wenxuan del <编号> [月份] [年份]   : 删出此年份此月份此编号的文选。
文选删除，并不自动删除主页精华区，如有必要，去主页删除。


        Snowman@SJ 06/04/1999

        Copyright 1997-1999 ShuJian MUD Wizard Group.
        All rights reserved.

        Visit our Homepage at - www.mymud.com

HELP);

    return 1;
}
