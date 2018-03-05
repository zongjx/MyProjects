package com.lab.zongjx.projmid;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.util.SparseArray;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

public class MyViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener{
    private SparseArray<View> mViews;
    private View mConvertiew;
    private Context mContext;
    private ImageView delete_item;
    public MyAdapter.OnItemClickListener mOnItemClickListener ;

    public MyViewHolder(Context context, View view, ViewGroup parent) {
        super(view);
        mConvertiew = view;
        mViews = new SparseArray<View>();
        mContext = context;

        delete_item = (ImageView) itemView.findViewById(R.id.delete_item);
        delete_item.setOnClickListener(this);
    }

    public static MyViewHolder get(Context context, ViewGroup parent, int layoutId) {
        View view = LayoutInflater.from(context).inflate(layoutId, parent, false);
        MyViewHolder holder = new MyViewHolder(context, view, parent);
        return holder;
    }

    public <T extends View> T getView(int viewId) {
        View view = mViews.get(viewId);
        if(view == null) {
            view = mConvertiew.findViewById(viewId);
            mViews.put(viewId,view);
        }
        return (T) view;
    }

    @Override
    public void onClick(View v) {
        if (mOnItemClickListener != null) {
            mOnItemClickListener.onItemClick(getAdapterPosition(), v);
        }
    }
}
